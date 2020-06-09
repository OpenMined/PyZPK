#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libsnark/common/routing_algorithms/as_waksman_routing_algorithm.cpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

void init_algorithms_as_waksman(py::module &m)
{

    // Binding for common/routing_algorithms/as_waksman_routing_algorithm.hpp
    // Declaration of interfaces for functionality for routing on an arbitrary-size (AS) Waksman network.
    m.def("as_waksman_top_height", &as_waksman_top_height, R"pbdoc(
        Return the height of the AS-Waksman network's top sub-network.
    )pbdoc",
          py::arg("num_packets"));
    m.def("as_waksman_switch_output", &as_waksman_switch_output, R"pbdoc(
        Return the input wire of a left-hand side switch of an AS-Waksman network for a given number of packets.
    )pbdoc",
          py::arg("num_packets"), py::arg("row_offset"), py::arg("row_idx"), py::arg("use_top"));
    m.def("as_waksman_switch_input", &as_waksman_switch_input, R"pbdoc(
        Return the input wire of a right-hand side switch of an AS-Waksman network for a given number of packets.
    )pbdoc",
          py::arg("num_packets"), py::arg("row_offset"), py::arg("row_idx"), py::arg("use_top"));
    m.def("as_waksman_num_columns", &as_waksman_num_columns, py::arg("num_packets"));
    m.def("construct_as_waksman_inner", &construct_as_waksman_inner, R"pbdoc(
        Construct AS-Waksman subnetwork
    )pbdoc",
          py::arg("left"), py::arg("right"), py::arg("lo"), py::arg("hi"), py::arg("rhs_dests"), py::arg("neighbors"));
    m.def("generate_as_waksman_topology", &generate_as_waksman_topology, py::arg("num_packets"));
    m.def("as_waksman_get_canonical_row_idx", &as_waksman_get_canonical_row_idx, R"pbdoc(
        Given either a position occupied either by its top or bottom ports, return the row index of its canonical position.
    )pbdoc",
          py::arg("row_offset"), py::arg("row_idx"));
    m.def("as_waksman_get_switch_setting_from_top_bottom_decision", &as_waksman_get_switch_setting_from_top_bottom_decision, R"pbdoc(
        Return a switch value that makes switch row_idx = as_waksman_switch_position_from_wire_position(row_offset, packet_idx) to 
        route the wire packet_idx via the top (if top = true), resp., bottom (if top = false) subnetwork.
    )pbdoc",
          py::arg("row_offset"), py::arg("packet_idx"), py::arg("use_top"));
    m.def("as_waksman_get_top_bottom_decision_from_switch_setting", &as_waksman_get_top_bottom_decision_from_switch_setting, R"pbdoc(
        Return true if the switch with input port at (column_idx, row_idx) when set to "straight" (if top = true), resp., "cross" 
        (if top = false), routes the packet at (column_idx, row_idx) via the top subnetwork.
    )pbdoc",
          py::arg("row_offset"), py::arg("packet_idx"), py::arg("switch_setting"));
    m.def("as_waksman_other_output_position", &as_waksman_other_output_position, R"pbdoc(
        Given an output wire of a RHS switch, compute and return the output position of the other wire also connected to this switch.
    )pbdoc",
          py::arg("row_offset"), py::arg("packet_idx"));
    m.def("as_waksman_other_input_position", &as_waksman_other_input_position, R"pbdoc(
        Given an input wire of a LHS switch, compute and return the input position of the other wire also connected to this switch.
    )pbdoc",
          py::arg("row_offset"), py::arg("packet_idx"));
    m.def("as_waksman_route_inner", &as_waksman_route_inner, R"pbdoc(
        Compute AS-Waksman switch settings for the subnetwork
    )pbdoc",
          py::arg("left"), py::arg("right"), py::arg("lo"), py::arg("hi"), py::arg("permutation"), py::arg("permutation_inv"), py::arg("routing"));
    m.def("get_as_waksman_routing", &get_as_waksman_routing, py::arg("permutation"));
    m.def("valid_as_waksman_routing", &valid_as_waksman_routing, py::arg("permutation"), py::arg("routing"));
}