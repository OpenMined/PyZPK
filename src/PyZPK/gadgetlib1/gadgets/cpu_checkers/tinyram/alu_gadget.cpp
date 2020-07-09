#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/tinyram/components/alu_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a protoboard for the TinyRAM ALU gadget.

void init_gadgetlib1_tinyram_alu_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<ALU_gadget<FieldT>, tinyram_standard_gadget<FieldT>>(m, "ALU_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const word_variable_gadget<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &ALU_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &ALU_gadget<FieldT>::generate_r1cs_witness);
}
