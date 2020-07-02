#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_gadgetlib1_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<gadget<FieldT>>(m, "gadget")
        .def(py::init<protoboard<FieldT> &, const std::string &>());
}