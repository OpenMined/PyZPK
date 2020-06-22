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
#include <libsnark/relations/circuit_satisfaction_problems/bacs/bacs.hpp>
#include <libsnark/relations/circuit_satisfaction_problems/bacs/examples/bacs_examples.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Declaration of interfaces for a BACS example, as well as functions to sample
// BACS examples with prescribed parameters
void init_relations_circuit_satisfaction_problems_bacs_examples(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    py::class_<bacs_example<FieldT>>(m, "bacs_example")
        .def(py::init<>())
        .def(py::init<const bacs_example<FieldT> &>())
        .def(py::init<const bacs_circuit<FieldT> &,
                      const bacs_primary_input<FieldT> &,
                      const bacs_auxiliary_input<FieldT> &>())
        .def_readwrite("circuit", &bacs_example<FieldT>::circuit)
        .def_readwrite("primary_input", &bacs_example<FieldT>::primary_input)
        .def_readwrite("auxiliary_input", &bacs_example<FieldT>::auxiliary_input);

    m.def("generate_bacs_example", &generate_bacs_example<FieldT>, py::arg("primary_input_size"), py::arg("auxiliary_input_size"), py::arg("num_gates"), py::arg("num_outputs"));

    m.def("random_linear_combination", [](const size_t num_variables) {
        const size_t terms = 1 + (std::rand() % 3);
        linear_combination<FieldT> result;
        for (size_t i = 0; i < terms; ++i)
        {
            const FieldT coeff = FieldT(std::rand());
            result = result + coeff * variable<FieldT>(std::rand() % (num_variables + 1));
        }
        return result;
    });
}
