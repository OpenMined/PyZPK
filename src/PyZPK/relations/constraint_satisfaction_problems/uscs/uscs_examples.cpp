#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/cast.h>
#include <pybind11/complex.h>
#include <vector>
#include <cassert>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/uscs/uscs.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/uscs/examples/uscs_examples.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Declaration of interfaces for a USCS example, as well as functions to sample
//  USCS examples with prescribed parameters
void init_relations_constraint_satisfaction_problems_uscs_examples(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    py::class_<uscs_example<FieldT>>(m, "uscs_example")
        .def(py::init<const uscs_constraint_system<FieldT> &,
                      const uscs_primary_input<FieldT> &,
                      const uscs_auxiliary_input<FieldT> &>())
        .def_readwrite("constraint_system", &uscs_example<FieldT>::constraint_system)
        .def_readwrite("primary_input", &uscs_example<FieldT>::primary_input)
        .def_readwrite("auxiliary_input", &uscs_example<FieldT>::auxiliary_input);
    
    m.def("generate_uscs_example_with_field_input", &generate_uscs_example_with_field_input<FieldT>, py::arg("num_constraints"), py::arg("num_inputs"));
    m.def("generate_uscs_example_with_binary_input", &generate_uscs_example_with_binary_input<FieldT>, py::arg("num_constraints"), py::arg("num_inputs"));
}
