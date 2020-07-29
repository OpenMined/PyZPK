#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <libsnark/gadgetlib2/infrastructure.hpp>

namespace py = pybind11;
using namespace gadgetlib2;

void init_gadgetlib2_infrastructure(py::module &m)
{
    m.def("safeConvert", &safeConvert, "Safely converts 64-bit types to 32-bit, or from unsigned to signed");

    py::class_<ErrorHandling>(m, "ErrorHandling")
        .def(py::init<>())
        .def_static("printStacktrace", &ErrorHandling::printStacktrace)
        .def_static("fatalError", py::overload_cast<const ::std::string&>(&ErrorHandling::fatalError), py::arg("msg"))
        .def_static("fatalError", py::overload_cast<const std::stringstream&>(&ErrorHandling::fatalError), py::arg("msg"));

    m.def("Log2", &Log2, "Returns Log2(input_number)");
    m.def("Log2ceil", &Log2ceil, "Returns Ceil value of Log2(input_number)");
    m.def("IsPower2", &IsPower2, "Returns True if input is power of 2 otherwise False");
    m.def("POW2", &POW2, "Return 2**input_number");
    m.def("CEIL", &CEIL, "Return CEIL value of input floating point  number");
}