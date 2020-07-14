#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_aux.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for auxiliary gadgets for the SHA256 gadget.

void declare_sha256_aux_lastbits_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<lastbits_gadget<FieldT>, gadget<FieldT>>(m, "lastbits_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_variable<FieldT> &,
                      const size_t,
                      const pb_variable<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &lastbits_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &lastbits_gadget<FieldT>::generate_r1cs_witness);
}

void declare_sha256_aux_XOR3_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<XOR3_gadget<FieldT>, gadget<FieldT>>(m, "XOR3_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const bool,
                      const pb_linear_combination<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &XOR3_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &XOR3_gadget<FieldT>::generate_r1cs_witness);
}

void declare_sha256_aux_small_sigma_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<small_sigma_gadget<FieldT>, gadget<FieldT>>(m, "small_sigma_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable<FieldT> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const std::string &>())
        .def("generate_r1cs_constraints", &small_sigma_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &small_sigma_gadget<FieldT>::generate_r1cs_witness);
}

void declare_sha256_aux_big_sigma_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<big_sigma_gadget<FieldT>, gadget<FieldT>>(m, "big_sigma_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable<FieldT> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const std::string &>())
        .def("generate_r1cs_constraints", &big_sigma_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &big_sigma_gadget<FieldT>::generate_r1cs_witness);
}

void declare_sha256_aux_choice_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<choice_gadget<FieldT>, gadget<FieldT>>(m, "choice_gadget")
        .def(py::init<protoboard<FieldT> &,
                  const pb_linear_combination_array<FieldT> &,
                  const pb_linear_combination_array<FieldT> &,
                  const pb_linear_combination_array<FieldT> &,
                  const pb_variable<FieldT> &,
                  const std::string &>())
        .def("generate_r1cs_constraints", &choice_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &choice_gadget<FieldT>::generate_r1cs_witness);
}

void declare_sha256_aux_majority_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<majority_gadget<FieldT>, gadget<FieldT>>(m, "majority_gadget")
        .def(py::init<protoboard<FieldT> &,
                  const pb_linear_combination_array<FieldT> &,
                  const pb_linear_combination_array<FieldT> &,
                  const pb_linear_combination_array<FieldT> &,
                  const pb_variable<FieldT> &,
                  const std::string &>())
        .def("generate_r1cs_constraints", &majority_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &majority_gadget<FieldT>::generate_r1cs_witness);
}

void init_gadgetlib1_hashes_sha256_aux_gadget(py::module &m)
{
    declare_sha256_aux_lastbits_gadget(m);
    declare_sha256_aux_XOR3_gadget(m);
    declare_sha256_aux_small_sigma_gadget(m);
    declare_sha256_aux_big_sigma_gadget(m);
    declare_sha256_aux_choice_gadget(m);
    declare_sha256_aux_majority_gadget(m);
}