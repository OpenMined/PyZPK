#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libsnark/relations/circuit_satisfaction_problems/tbcs/examples/tbcs_examples.hpp>

namespace py = pybind11;
using namespace libsnark;

// A TBCS example comprises a TBCS circuit, TBCS primary input, and TBCS auxiliary input.
void init_relations_circuit_satisfaction_problems_tbcs_examples(py::module &m)
{
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
