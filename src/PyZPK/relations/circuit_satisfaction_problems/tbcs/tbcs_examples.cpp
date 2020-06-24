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
#include <libsnark/relations/circuit_satisfaction_problems/tbcs/tbcs.hpp>
#include <libsnark/relations/circuit_satisfaction_problems/tbcs/examples/tbcs_examples.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// A TBCS example comprises a TBCS circuit, TBCS primary input, and TBCS auxiliary input.
void init_relations_circuit_satisfaction_problems_tbcs_examples(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    py::class_<tbcs_example>(m, "tbcs_example")
        .def(py::init<>())
        .def(py::init<const tbcs_example &>())
        .def(py::init<const tbcs_circuit &,
                      const tbcs_primary_input &,
                      const tbcs_auxiliary_input &>())
        .def_readwrite("circuit", &tbcs_example::circuit)
        .def_readwrite("primary_input", &tbcs_example::primary_input)
        .def_readwrite("auxiliary_input", &tbcs_example::auxiliary_input);
}
