#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for top-level SHA256 gadgets.

// Gadget for the SHA256 compression function.
void declare_sha256_compression_function_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<sha256_compression_function_gadget<FieldT>, gadget<FieldT>>(m, "sha256_compression_function_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const digest_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &sha256_compression_function_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &sha256_compression_function_gadget<FieldT>::generate_r1cs_witness);
}

// Gadget for the SHA256 compression function, viewed as a 2-to-1 hash
// function, and using the same initialization vector as in SHA256
// specification. Thus, any collision for
// sha256_two_to_one_hash_gadget trivially extends to a collision for
// full SHA256 (by appending the same padding).
void declare_sha256_two_to_one_hash_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<sha256_two_to_one_hash_gadget<FieldT>, gadget<FieldT>>(m, "sha256_two_to_one_hash_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const digest_variable<FieldT> &,
                      const digest_variable<FieldT> &,
                      const digest_variable<FieldT> &,
                      const std::string &>())
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const block_variable<FieldT> &,
                      const digest_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &sha256_two_to_one_hash_gadget<FieldT>::generate_r1cs_constraints, py::arg("ensure_output_bitness"))
        .def("generate_r1cs_witness", &sha256_two_to_one_hash_gadget<FieldT>::generate_r1cs_witness)
        .def_static("get_digest_len", &sha256_two_to_one_hash_gadget<FieldT>::get_digest_len)
        .def_static("get_block_len", &sha256_two_to_one_hash_gadget<FieldT>::get_block_len)
        .def_static("get_hash", &sha256_two_to_one_hash_gadget<FieldT>::get_hash, py::arg("input"))
        .def_static("expected_constraints", &sha256_two_to_one_hash_gadget<FieldT>::expected_constraints, py::arg("ensure_output_bitness"));
}

void init_gadgetlib1_hashes_sha256_gadget(py::module &m)
{
    declare_sha256_compression_function_gadget(m);
    declare_sha256_two_to_one_hash_gadget(m);
}