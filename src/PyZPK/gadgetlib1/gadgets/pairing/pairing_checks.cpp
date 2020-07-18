#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/pairing/pairing_checks.hpp>
#include <libsnark/gadgetlib1/gadgets/pairing/mnt_pairing_params.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for pairing-check gadgets.

//  Given that e(.,.) denotes a pairing,
//  - the gadget "check_e_equals_e_gadget" checks the equation "e(P1,Q1)=e(P2,Q2)"; and
void init_gadgetlib1_pairing_pairing_checks(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<check_e_equals_e_gadget<ppT>, gadget<FieldT>>(m, "check_e_equals_e_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &check_e_equals_e_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &check_e_equals_e_gadget<ppT>::generate_r1cs_witness);
}