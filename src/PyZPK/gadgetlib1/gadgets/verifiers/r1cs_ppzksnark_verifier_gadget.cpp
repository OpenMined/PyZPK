#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/gadgetlib1/gadgets/verifiers/r1cs_ppzksnark_verifier_gadget.hpp>
#include <libsnark/gadgetlib1/gadgets/pairing/mnt_pairing_params.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for the the R1CS ppzkSNARK verifier gadget.

//  The gadget r1cs_ppzksnark_verifier_gadget verifiers correct computation of r1cs_ppzksnark_verifier_strong_IC.
//  The gadget is built from two main sub-gadgets:
//  - r1cs_ppzksnark_verifier_process_vk_gadget, which verifies correct computation of r1cs_ppzksnark_verifier_process_vk, and
//  - r1cs_ppzksnark_online_verifier_gadget, which verifies correct computation of r1cs_ppzksnark_online_verifier_strong_IC.
//  See r1cs_ppzksnark.hpp for description of the aforementioned functions.

void declare_r1cs_ppzksnark_proof_variable(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_proof_variable<ppT>, gadget<FieldT>>(m, "r1cs_ppzksnark_proof_variable")
        .def(py::init<protoboard<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &r1cs_ppzksnark_proof_variable<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &r1cs_ppzksnark_proof_variable<ppT>::generate_r1cs_witness);
}

void declare_r1cs_ppzksnark_verification_key_variable(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_verification_key_variable<ppT>, gadget<FieldT>>(m, "r1cs_ppzksnark_verification_key_variable")
        .def(py::init<protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const size_t,
                      const std::string &>())
        .def("generate_r1cs_constraints", &r1cs_ppzksnark_verification_key_variable<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", py::overload_cast<const r1cs_ppzksnark_verification_key<other_curve<ppT>> &>(&r1cs_ppzksnark_verification_key_variable<ppT>::generate_r1cs_witness), py::arg("vk"))
        .def("generate_r1cs_witness", py::overload_cast<const libff::bit_vector &>(&r1cs_ppzksnark_verification_key_variable<ppT>::generate_r1cs_witness), py::arg("vk"))
        .def("get_bits", &r1cs_ppzksnark_verification_key_variable<ppT>::get_bits)
        .def_static("get_verification_key_bits", &r1cs_ppzksnark_verification_key_variable<ppT>::get_verification_key_bits);
}

void declare_r1cs_ppzksnark_preprocessed_r1cs_ppzksnark_verification_key_variable(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_preprocessed_r1cs_ppzksnark_verification_key_variable<ppT>>(m, "r1cs_ppzksnark_preprocessed_r1cs_ppzksnark_verification_key_variable")
        .def(py::init<>())
        .def(py::init<protoboard<FieldT> &,
                      const r1cs_ppzksnark_verification_key<other_curve<ppT>> &,
                      const std::string &>());
}

void declare_r1cs_ppzksnark_verifier_process_vk_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_verifier_process_vk_gadget<ppT>, gadget<FieldT>>(m, "r1cs_ppzksnark_verifier_process_vk_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const r1cs_ppzksnark_verification_key_variable<ppT> &,
                      r1cs_ppzksnark_preprocessed_r1cs_ppzksnark_verification_key_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &r1cs_ppzksnark_verifier_process_vk_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &r1cs_ppzksnark_verifier_process_vk_gadget<ppT>::generate_r1cs_witness);
}

void declare_r1cs_ppzksnark_online_verifier_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_online_verifier_gadget<ppT>, gadget<FieldT>>(m, "r1cs_ppzksnark_online_verifier_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const r1cs_ppzksnark_preprocessed_r1cs_ppzksnark_verification_key_variable<ppT> &,
                      const pb_variable_array<FieldT> &,
                      const size_t,
                      const r1cs_ppzksnark_proof_variable<ppT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &r1cs_ppzksnark_online_verifier_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &r1cs_ppzksnark_online_verifier_gadget<ppT>::generate_r1cs_witness);
}

void declare_r1cs_ppzksnark_verifier_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_verifier_gadget<ppT>, gadget<FieldT>>(m, "r1cs_ppzksnark_verifier_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const r1cs_ppzksnark_verification_key_variable<ppT> &,
                      const pb_variable_array<FieldT> &,
                      const size_t,
                      const r1cs_ppzksnark_proof_variable<ppT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &r1cs_ppzksnark_verifier_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &r1cs_ppzksnark_verifier_gadget<ppT>::generate_r1cs_witness);
}

void init_gadgetlib1_verifiers_r1cs_ppzksnark_verifier_gadget(py::module &m)
{
    declare_r1cs_ppzksnark_proof_variable(m);
    declare_r1cs_ppzksnark_verification_key_variable(m);
    declare_r1cs_ppzksnark_preprocessed_r1cs_ppzksnark_verification_key_variable(m);
    declare_r1cs_ppzksnark_verifier_process_vk_gadget(m);
    declare_r1cs_ppzksnark_online_verifier_gadget(m);
    declare_r1cs_ppzksnark_verifier_gadget(m);
}