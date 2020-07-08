#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/tinyram/components/alu_arithmetic.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a protoboard for the TinyRAM ALU arithmetic gadgets.
// These gadget check the correct execution of arithmetic TinyRAM instructions.
void declare_tinyram_alu_arithmetic_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_arithmetic_gadget<FieldT>, tinyram_standard_gadget<FieldT>>(m, "ALU_arithmetic_gadget");
}

void declare_tinyram_ALU_and_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_and_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_and_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_and_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_and_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_or_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_or_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_or_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_or_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_or_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_xor_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_xor_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_xor_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_xor_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_xor_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_not_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_not_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_not_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_not_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_not_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_add_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_add_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_add_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_add_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_add_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_sub_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_sub_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_sub_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_sub_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_sub_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_mov_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_mov_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_mov_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_mov_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_mov_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_cmov_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_cmov_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_cmov_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_cmov_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_cmov_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_cmp_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_cmp_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_cmp_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_cmp_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_cmp_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_cmps_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_cmps_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_cmps_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_cmps_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_cmps_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_umul_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_umul_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_umul_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_umul_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_umul_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_smul_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_smul_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_smul_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_smul_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_smul_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_divmod_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_divmod_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_divmod_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_divmod_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_divmod_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_shr_shl_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_shr_shl_gadget<FieldT>, ALU_arithmetic_gadget<FieldT>>(m, "ALU_shr_shl_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_shr_shl_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_shr_shl_gadget<FieldT>::generate_r1cs_witness);
}

void init_gadgetlib1_tinyram_alu_arithmetic(py::module &m)
{
    declare_tinyram_alu_arithmetic_gadget(m);
    declare_tinyram_ALU_and_gadget(m);
    declare_tinyram_ALU_or_gadget(m);
    declare_tinyram_ALU_xor_gadget(m);
    declare_tinyram_ALU_not_gadget(m);
    declare_tinyram_ALU_add_gadget(m);
    declare_tinyram_ALU_mov_gadget(m);
    declare_tinyram_ALU_cmov_gadget(m);
    declare_tinyram_ALU_cmp_gadget(m);
    declare_tinyram_ALU_cmps_gadget(m);
    declare_tinyram_ALU_umul_gadget(m);
    declare_tinyram_ALU_smul_gadget(m);
    declare_tinyram_ALU_divmod_gadget(m);
    declare_tinyram_ALU_shr_shl_gadget(m);
}