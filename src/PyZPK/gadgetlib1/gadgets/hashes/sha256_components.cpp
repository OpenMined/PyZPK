#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_components.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for gadgets for the SHA256 message schedule and round function.

void declare_sha256_message_schedule_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    m.attr("SHA256_digest_size") = 256;
    m.attr("SHA256_block_size") = 512;

    py::class_<sha256_message_schedule_gadget<FieldT>, gadget<FieldT>>(m, "sha256_message_schedule_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &sha256_message_schedule_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &sha256_message_schedule_gadget<FieldT>::generate_r1cs_witness);
}

void declare_sha256_round_function_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<sha256_round_function_gadget<FieldT>, gadget<FieldT>>(m, "sha256_round_function_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_variable<FieldT> &,
                      const long &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &sha256_round_function_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &sha256_round_function_gadget<FieldT>::generate_r1cs_witness);
}

void init_gadgetlib1_hashes_sha256_components(py::module &m)
{
    declare_sha256_message_schedule_gadget(m);
    declare_sha256_round_function_gadget(m);
}