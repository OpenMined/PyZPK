#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <libsnark/gadgetlib2/integration.hpp>

namespace py = pybind11;
using namespace libsnark;

void init_gadgetlib2_integration(py::module &m)
{
    m.def("get_constraint_system_from_gadgetlib2", &get_constraint_system_from_gadgetlib2, py::arg("Protoboard"));
    m.def("get_variable_assignment_from_gadgetlib2", &get_variable_assignment_from_gadgetlib2, py::arg("Protoboard"));
}