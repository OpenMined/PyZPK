#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <vector>
#include <libsnark/relations/ram_computations/memory/memory_store_trace.hpp>
#include <libsnark/relations/ram_computations/memory/ra_memory.hpp>
namespace py = pybind11;
using namespace libsnark;

//  A list in which each component consists of a timestamp and a memory store.
void init_relations_ram_computations_memory_store_trace(py::module &m)
{
    py::class_<memory_store_trace>(m, "memory_store_trace")
        .def(py::init<>())
        .def("get_trace_entry", &memory_store_trace::get_trace_entry, py::arg("timestamp"))
        .def("set_trace_entry", &memory_store_trace::set_trace_entry, py::arg("timestamp"), py::arg("address_and_value"));
}

void init_relations_ram_computations_ra_memory(py::module &m)
{
    py::class_<ra_memory>(m, "ra_memory")
        .def(py::init<const size_t, const size_t>())
        .def(py::init<const size_t, const size_t, const std::vector<size_t> &>())
        .def(py::init<const size_t, const size_t, const memory_contents &>())

        .def("get_value", &ra_memory::get_value, py::arg("address"))
        .def("set_value", &ra_memory::set_value, py::arg("address"), py::arg("value"));
}