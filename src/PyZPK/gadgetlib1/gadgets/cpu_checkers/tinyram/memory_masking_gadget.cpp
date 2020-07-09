#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/tinyram/components/memory_masking_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a protoboard for the TinyRAM ALU consistency enforcer gadget.

void init_gadgetlib1_tinyram_memory_masking_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<memory_masking_gadget<FieldT>, tinyram_standard_gadget<FieldT>>(m, "memory_masking_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const doubleword_variable_gadget<FieldT> &,
                      const dual_variable_gadget<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const doubleword_variable_gadget<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &memory_masking_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &memory_masking_gadget<FieldT>::generate_r1cs_witness);
}
