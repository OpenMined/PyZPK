#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/r1cs/examples/r1cs_examples.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Declaration of interfaces for a R1CS example, as well as functions to sample
// R1CS examples with prescribed parameters (according to some distribution)
void init_relations_constraint_satisfaction_problems_r1cs_examples(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    py::class_<r1cs_example<FieldT>>(m, "r1cs_example")
        .def(py::init<const r1cs_constraint_system<FieldT> &,
                      const r1cs_primary_input<FieldT> &,
                      const r1cs_auxiliary_input<FieldT> &>())
        .def_readwrite("constraint_system", &r1cs_example<FieldT>::constraint_system)
        .def_readwrite("primary_input", &r1cs_example<FieldT>::primary_input)
        .def_readwrite("auxiliary_input", &r1cs_example<FieldT>::auxiliary_input);

    m.def("generate_r1cs_example_with_field_input", &generate_r1cs_example_with_field_input<FieldT>, py::arg("num_constraints"), py::arg("num_inputs"));
    m.def("generate_r1cs_example_with_binary_input", &generate_r1cs_example_with_binary_input<FieldT>, py::arg("num_constraints"), py::arg("num_inputs"));
    
    using FieldTbn = Fp_model<4l, libff::alt_bn128_modulus_r>;
    m.def("generate_r1cs_example_with_binary_inputbn", &generate_r1cs_example_with_binary_input<FieldTbn>);    
}