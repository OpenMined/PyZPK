#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <unordered_set>
#include <iostream>
#include <libff/common/serialization.hpp>
#include <libsnark/common/data_structures/integer_permutation.hpp>
#include <libsnark/common/data_structures/set_commitment.hpp>
#include <libsnark/common/routing_algorithms/benes_routing_algorithm.cpp>
#include <libsnark/common/routing_algorithms/as_waksman_routing_algorithm.cpp>
using namespace std;
using namespace libsnark;
namespace py = pybind11;

PYBIND11_MODULE(pyzpk, m)
{
    m.doc() = "Python wrapper for open source Zero Proof Knowledge Library";

    // Binding for common/data_structures/integer_permutation.cpp
    py::class_<integer_permutation>(m, "integer_permutation")
        .def(py::init<const size_t>())
        .def(py::init<const size_t, const size_t>())
        .def("set", &integer_permutation::set, py::arg("position"), py::arg("value"))
        .def("get", &integer_permutation::get, py::arg("position"))
        .def("size", &integer_permutation::size)
        .def("is_valid", &integer_permutation::is_valid)
        .def("inverse", &integer_permutation::inverse)
        .def("slice", &integer_permutation::slice, py::arg("slice_min_element"), py::arg("slice_max_element"))
        .def("next_permutation", &integer_permutation::next_permutation)
        .def("random_shuffle", &integer_permutation::random_shuffle)
        .def(
            "__eq__", [](integer_permutation const &self, integer_permutation const &other) { return self == other; }, py::is_operator());

    // Binding for common/data_structures/set_commitment.cpp // set_membership_proof
    py::class_<set_membership_proof>(m, "set_membership_proof")
        .def("size_in_bits", &set_membership_proof::size_in_bits)
        .def(
            "__eq__", [](set_membership_proof const &self, set_membership_proof const &other) { return self == other; }, py::is_operator());

    // Todo
    // std::ostream& operator<<(std::ostream &out, const set_membership_proof &proof)
    // std::istream& operator>>(std::istream &in, set_membership_proof &proof)

    // Binding for common/routing_algorithms/benes_routing_algorithm.hpp
    // Declaration of interfaces for functionality for routing on a Benes network.
    m.def("benes_cross_edge_mask", &benes_cross_edge_mask, R"pbdoc(
        Compute the mask for all the cross edges originating at a particular column.
    )pbdoc", py::arg("dimension"), py::arg("column_idx"));
    m.def("benes_lhs_packet_destination", &benes_lhs_packet_destination, R"pbdoc(
            Return the specified destination of packet of the left-hand side of the routing network, based on the subnetwork
    )pbdoc", py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"), py::arg("use_top"));
    m.def("benes_rhs_packet_source", &benes_rhs_packet_source, R"pbdoc(
        Return the specified source of packet of the right-hand side of the routing network, based on the subnetwork
    )pbdoc", py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"), py::arg("use_top"));
    m.def("benes_get_switch_setting_from_subnetwork", &benes_get_switch_setting_from_subnetwork, R"pbdoc(
        For a switch located at column_idx-th column and row_idx-th row, return the switch setting that would route its packet 
        using the top subnetwork.
    )pbdoc", py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"), py::arg("use_top"));
    m.def("benes_packet_cross_destination", &benes_packet_cross_destination, R"pbdoc(
        A packet column_idx-th column and row_idx-th row of the routing network has two destinations (see comment by benes_cross_edge_mask),
        this returns row_idx' of the "cross" destination.
    )pbdoc", py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"));
    m.def("benes_packet_cross_source", &benes_packet_cross_source, R"pbdoc(
         A packet column_idx-th column and row_idx-th row of the routing network has two source packets that could give rise to it, this
        returns row_idx' of the "cross" source packet.
    )pbdoc", py::arg("dimension"), py::arg("column_idx"), py::arg("packet_idx"));
    m.def("benes_num_columns", &benes_num_columns, py::arg("num_packets"));
    m.def("generate_benes_topology", &generate_benes_topology, py::arg("num_packets"));
    m.def("route_benes_inner", &route_benes_inner, py::arg("dimension"), py::arg("permutation"), py::arg("permutation_inv"), py::arg("column_idx_start"), py::arg("column_idx_end"), py::arg("subnetwork_offset"), py::arg("subnetwork_size"), py::arg("routing"));
    m.def("get_benes_routing", &get_benes_routing, py::arg("permutation"));
    m.def("valid_benes_routing", &valid_benes_routing, py::arg("permutation"), py::arg("routing"));
    // Todo
    // template<typename T>
    // std::vector<std::vector<T> > route_by_benes(const benes_routing &routing, const std::vector<T> &start)

    // Binding for common/routing_algorithms/as_waksman_routing_algorithm.hpp
    // Declaration of interfaces for functionality for routing on an arbitrary-size (AS) Waksman network.
    m.def("as_waksman_top_height", &as_waksman_top_height, R"pbdoc(
        Return the height of the AS-Waksman network's top sub-network.
    )pbdoc", py::arg("num_packets"));
    m.def("as_waksman_switch_output", &as_waksman_switch_output, R"pbdoc(
        Return the input wire of a left-hand side switch of an AS-Waksman network for a given number of packets.
    )pbdoc", py::arg("num_packets"), py::arg("row_offset"), py::arg("row_idx"), py::arg("use_top") );
    m.def("as_waksman_switch_input", &as_waksman_switch_input, R"pbdoc(
        Return the input wire of a right-hand side switch of an AS-Waksman network for a given number of packets.
    )pbdoc", py::arg("num_packets"), py::arg("row_offset"), py::arg("row_idx"), py::arg("use_top"));
    m.def("as_waksman_num_columns", &as_waksman_num_columns, py::arg("num_packets"));
    m.def("construct_as_waksman_inner", &construct_as_waksman_inner, R"pbdoc(
        Construct AS-Waksman subnetwork
    )pbdoc", py::arg("left"), py::arg("right"), py::arg("lo"), py::arg("hi"), py::arg("rhs_dests"), py::arg("neighbors"));
    m.def("generate_as_waksman_topology", &generate_as_waksman_topology, py::arg("num_packets"));
    m.def("as_waksman_get_canonical_row_idx", &as_waksman_get_canonical_row_idx, R"pbdoc(
        Given either a position occupied either by its top or bottom ports, return the row index of its canonical position.
    )pbdoc", py::arg("row_offset"), py::arg("row_idx"));
    m.def("as_waksman_get_switch_setting_from_top_bottom_decision", &as_waksman_get_switch_setting_from_top_bottom_decision, R"pbdoc(
        Return a switch value that makes switch row_idx = as_waksman_switch_position_from_wire_position(row_offset, packet_idx) to 
        route the wire packet_idx via the top (if top = true), resp., bottom (if top = false) subnetwork.
    )pbdoc", py::arg("row_offset"), py::arg("packet_idx"), py::arg("use_top"));
    m.def("as_waksman_get_top_bottom_decision_from_switch_setting", &as_waksman_get_top_bottom_decision_from_switch_setting ,R"pbdoc(
        Return true if the switch with input port at (column_idx, row_idx) when set to "straight" (if top = true), resp., "cross" 
        (if top = false), routes the packet at (column_idx, row_idx) via the top subnetwork.
    )pbdoc", py::arg("row_offset"), py::arg("packet_idx"), py::arg("switch_setting"));
    m.def("as_waksman_other_output_position", &as_waksman_other_output_position ,R"pbdoc(
        Given an output wire of a RHS switch, compute and return the output position of the other wire also connected to this switch.
    )pbdoc", py::arg("row_offset"), py::arg("packet_idx"));
    m.def("as_waksman_other_input_position", &as_waksman_other_input_position ,R"pbdoc(
        Given an input wire of a LHS switch, compute and return the input position of the other wire also connected to this switch.
    )pbdoc", py::arg("row_offset"), py::arg("packet_idx"));
    m.def("as_waksman_route_inner", &as_waksman_route_inner ,R"pbdoc(
        Compute AS-Waksman switch settings for the subnetwork
    )pbdoc", py::arg("left"), py::arg("right"), py::arg("lo"), py::arg("hi"), py::arg("permutation"), py::arg("permutation_inv"), py::arg("routing"));
    m.def("get_as_waksman_routing", &get_as_waksman_routing, py::arg("permutation"));
    m.def("valid_as_waksman_routing", &valid_as_waksman_routing, py::arg("permutation"), py::arg("routing"));
}
