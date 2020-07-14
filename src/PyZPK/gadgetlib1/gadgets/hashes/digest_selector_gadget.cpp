#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/digest_selector_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_gadgetlib1_hashes_digest_selector_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<digest_selector_gadget<FieldT>, gadget<FieldT>>(m, "digest_selector_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const digest_variable<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const digest_variable<FieldT> &,
                      const digest_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &digest_selector_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &digest_selector_gadget<FieldT>::generate_r1cs_witness);
}