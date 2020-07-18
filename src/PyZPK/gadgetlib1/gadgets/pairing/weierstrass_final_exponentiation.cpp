#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/pairing/weierstrass_final_exponentiation.hpp>
#include <libsnark/gadgetlib1/gadgets/pairing/mnt_pairing_params.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for final exponentiation gadgets.
// The gadgets verify final exponentiation for Weiersrass curves

// Gadget for final exponentiation with embedding degree 6.
void init_gadgetlib1_pairing_weierstrass_final_exponentiation(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<mnt6_final_exp_gadget<ppT>, gadget<FieldT>>(m, "mnt6_final_exp_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const Fqk_variable<ppT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &mnt6_final_exp_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &mnt6_final_exp_gadget<ppT>::generate_r1cs_witness);
}