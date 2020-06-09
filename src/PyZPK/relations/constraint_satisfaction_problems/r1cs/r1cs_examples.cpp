#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>
#include <vector>
#include <cassert>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/r1cs/examples/r1cs_examples.hpp>
#define FieldT libff::Fr<libff::mnt6_pp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

// Declaration of interfaces for a R1CS example, as well as functions to sample
// R1CS examples with prescribed parameters (according to some distribution).
void init_relations_constraint_satisfaction_problems_r1cs_examples(py::module &m)
{
    py::class_<r1cs_constraint_system<FieldT>>(m, "r1cs_constraint_system")
        .def(py::init<>())
        .def("is_satisfied", &r1cs_constraint_system<FieldT>::is_satisfied);

    py::class_<r1cs_example<FieldT>>(m, "r1cs_example")
        .def(py::init<const r1cs_constraint_system<FieldT> &,
                      const r1cs_primary_input<FieldT> &,
                      const r1cs_auxiliary_input<FieldT> &>())
        .def_readwrite("constraint_system", &r1cs_example<FieldT>::constraint_system)
        .def_readwrite("primary_input", &r1cs_example<FieldT>::primary_input)
        .def_readwrite("auxiliary_input", &r1cs_example<FieldT>::auxiliary_input);
        
    m.def("generate_r1cs_example_with_field_input", &generate_r1cs_example_with_field_input<FieldT>, py::arg("num_constraints"), py::arg("num_inputs"));
    m.def("generate_r1cs_example_with_binary_input", &generate_r1cs_example_with_binary_input<FieldT>, py::arg("num_constraints"), py::arg("num_inputs"));
}