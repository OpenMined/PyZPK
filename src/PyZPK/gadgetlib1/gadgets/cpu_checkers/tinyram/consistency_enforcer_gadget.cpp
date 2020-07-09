#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/tinyram/components/consistency_enforcer_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a protoboard for the TinyRAM ALU consistency enforcer gadget.

void init_gadgetlib1_tinyram_consistency_enforcer_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<consistency_enforcer_gadget<FieldT>, tinyram_standard_gadget<FieldT>>(m, "consistency_enforcer_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &consistency_enforcer_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &consistency_enforcer_gadget<FieldT>::generate_r1cs_witness);
}
