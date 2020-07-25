#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <libsnark/gadgetlib2/pp.hpp>

namespace py = pybind11;
using namespace gadgetlib2;

// Declaration of PublicParams for Fp field arithmetic
void init_gadgetlib2_pp(py::module &m)
{
    py::class_<PublicParams>(m, "PublicParams")
        .def(py::init<const std::size_t>())
        .def_readwrite("log_p", &PublicParams::log_p)
        .def("getFp", &PublicParams::getFp);
    
    m.def("initPublicParamsFromDefaultPp", &initPublicParamsFromDefaultPp);
}