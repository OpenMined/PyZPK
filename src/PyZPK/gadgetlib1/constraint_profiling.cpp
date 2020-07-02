#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/gadgetlib1/constraint_profiling.hpp>

namespace py = pybind11;
using namespace libsnark;

void init_gadgetlib1_constraint_profiling(py::module &m)
{
    m.attr("constraint_profiling_indent") = 0;

    py::class_<constraint_profiling_entry>(m, "constraint_profiling_entry")
        .def_readwrite("indent", &constraint_profiling_entry::indent)
        .def_readwrite("annotation", &constraint_profiling_entry::annotation)
        .def_readwrite("count", &constraint_profiling_entry::count);

    m.def("PRINT_CONSTRAINT_PROFILING", &PRINT_CONSTRAINT_PROFILING, "returns # of top level constraints");
}