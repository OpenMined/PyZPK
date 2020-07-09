#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/tinyram/components/alu_control_flow.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for the TinyRAM ALU control-flow gadgets.
// These gadget check the correct execution of control-flow TinyRAM instructions.

void declare_tinyram_ALU_control_flow_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_control_flow_gadget<FieldT>, tinyram_standard_gadget<FieldT>>(m, "ALU_control_flow_gadget");
}

void declare_tinyram_ALU_jmp_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_jmp_gadget<FieldT>, ALU_control_flow_gadget<FieldT>>(m, "ALU_jmp_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_jmp_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_jmp_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_cjmp_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_cjmp_gadget<FieldT>, ALU_control_flow_gadget<FieldT>>(m, "ALU_cjmp_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_cjmp_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_cjmp_gadget<FieldT>::generate_r1cs_witness);
}

void declare_tinyram_ALU_cnjmp_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_cnjmp_gadget<FieldT>, ALU_control_flow_gadget<FieldT>>(m, "ALU_cnjmp_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_cnjmp_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_cnjmp_gadget<FieldT>::generate_r1cs_witness);
}

void init_gadgetlib1_tinyram_alu_control_flow(py::module &m)
{
    declare_tinyram_ALU_control_flow_gadget(m);
    declare_tinyram_ALU_jmp_gadget(m);
    declare_tinyram_ALU_cjmp_gadget(m);
    declare_tinyram_ALU_cnjmp_gadget(m);
}