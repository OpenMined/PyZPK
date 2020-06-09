#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libsnark/common/routing_algorithms/benes_routing_algorithm.cpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

void init_algorithms_benes(py::module &m)
{

    // Binding for common/routing_algorithms/benes_routing_algorithm.hpp
    // Declaration of interfaces for functionality for routing on a Benes network.
    m.def("benes_cross_edge_mask", &benes_cross_edge_mask, R"pbdoc(
        Compute the mask for all the cross edges originating at a particular column.
    )pbdoc",
          py::arg("dimension"), py::arg("column_idx"));
    m.def("benes_lhs_packet_destination", &benes_lhs_packet_destination, R"pbdoc(
            Return the specified destination of packet of the left-hand side of the routing network, based on the subnetwork
    )pbdoc",
          py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"), py::arg("use_top"));
    m.def("benes_rhs_packet_source", &benes_rhs_packet_source, R"pbdoc(
        Return the specified source of packet of the right-hand side of the routing network, based on the subnetwork
    )pbdoc",
          py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"), py::arg("use_top"));
    m.def("benes_get_switch_setting_from_subnetwork", &benes_get_switch_setting_from_subnetwork, R"pbdoc(
        For a switch located at column_idx-th column and row_idx-th row, return the switch setting that would route its packet 
        using the top subnetwork.
    )pbdoc",
          py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"), py::arg("use_top"));
    m.def("benes_packet_cross_destination", &benes_packet_cross_destination, R"pbdoc(
        A packet column_idx-th column and row_idx-th row of the routing network has two destinations (see comment by benes_cross_edge_mask),
        this returns row_idx' of the "cross" destination.
    )pbdoc",
          py::arg("dimension"), py::arg("column_idx"), py::arg("row_idx"));
    m.def("benes_packet_cross_source", &benes_packet_cross_source, R"pbdoc(
         A packet column_idx-th column and row_idx-th row of the routing network has two source packets that could give rise to it, this
        returns row_idx' of the "cross" source packet.
    )pbdoc",
          py::arg("dimension"), py::arg("column_idx"), py::arg("packet_idx"));
    m.def("benes_num_columns", &benes_num_columns, py::arg("num_packets"));
    m.def("generate_benes_topology", &generate_benes_topology, py::arg("num_packets"));
    m.def("route_benes_inner", &route_benes_inner, py::arg("dimension"), py::arg("permutation"), py::arg("permutation_inv"), py::arg("column_idx_start"), py::arg("column_idx_end"), py::arg("subnetwork_offset"), py::arg("subnetwork_size"), py::arg("routing"));
    m.def("get_benes_routing", &get_benes_routing, py::arg("permutation"));
    m.def("valid_benes_routing", &valid_benes_routing, py::arg("permutation"), py::arg("routing"));
    // Todo
    // template<typename T>
    // std::vector<std::vector<T> > route_by_benes(const benes_routing &routing, const std::vector<T> &start)
}