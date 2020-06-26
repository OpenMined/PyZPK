#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/relations/circuit_satisfaction_problems/bacs/bacs.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a a BACS variable assignment, a BACS gate, a BACS primary input,
// a BACS auxiliary input, a BACS circuit
void init_relations_circuit_satisfaction_problems_bacs(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    // A BACS gate is a formal expression of the form lhs * rhs = output ,
    // where lhs and rhs are linear combinations (of variables) and output is a variable.
    py::class_<bacs_gate<FieldT>>(m, "bacs_gate")
        .def(py::init<>())
        .def_readwrite("lhs", &bacs_gate<FieldT>::lhs)
        .def_readwrite("rhs", &bacs_gate<FieldT>::rhs)
        .def_readwrite("output", &bacs_gate<FieldT>::output)
        .def_readwrite("is_circuit_output", &bacs_gate<FieldT>::is_circuit_output)
        .def("evaluate", &bacs_gate<FieldT>::evaluate, py::arg("input"))
        .def("print", &bacs_gate<FieldT>::print, py::arg("variable_annotations"))
        .def(
            "__eq__", [](bacs_gate<FieldT> const &self, bacs_gate<FieldT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](bacs_gate<FieldT> const &self) {
            std::ostringstream os;
            os << (self.is_circuit_output ? 1 : 0) << "\n";
            os << self.lhs << OUTPUT_NEWLINE;
            os << self.rhs << OUTPUT_NEWLINE;
            os << self.output.index << "\n";
            return os;
        })
        .def("__istr__", [](bacs_gate<FieldT> &self) {
            std::istringstream os;
            size_t tmp;
            os >> tmp;
            libff::consume_newline(os);
            self.is_circuit_output = (tmp != 0 ? true : false);
            os >> self.lhs;
            libff::consume_OUTPUT_NEWLINE(os);
            os >> self.rhs;
            libff::consume_OUTPUT_NEWLINE(os);
            os >> self.output.index;
            libff::consume_newline(os);
            return os;
        });

    // A BACS circuit is an arithmetic circuit in which every gate is a BACS gate.
    // Given a BACS primary input and a BACS auxiliary input, the circuit can be evaluated.
    // If every output evaluates to zero, then the circuit is satisfied.

    // NOTE:
    // The 0-th variable (i.e., "x_{0}") always represents the constant 1.
    // Thus, the 0-th variable is not included in num_variables.
    py::class_<bacs_circuit<FieldT>>(m, "bacs_circuit")
        .def(py::init<>())
        .def_readwrite("primary_input_size", &bacs_circuit<FieldT>::primary_input_size)
        .def_readwrite("auxiliary_input_size", &bacs_circuit<FieldT>::auxiliary_input_size)
        .def_readwrite("gates", &bacs_circuit<FieldT>::gates)
        .def("num_inputs", &bacs_circuit<FieldT>::num_inputs)
        .def("num_gates", &bacs_circuit<FieldT>::num_gates)
        .def("num_wires", &bacs_circuit<FieldT>::num_wires)
        .def("wire_depths", &bacs_circuit<FieldT>::wire_depths)
        .def("depth", &bacs_circuit<FieldT>::depth)
        .def("is_valid", &bacs_circuit<FieldT>::is_valid)
        .def("is_satisfied", &bacs_circuit<FieldT>::is_satisfied, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def("get_all_outputs", &bacs_circuit<FieldT>::get_all_outputs, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def("get_all_wires", &bacs_circuit<FieldT>::get_all_wires, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def("add_gate", py::overload_cast<const bacs_gate<FieldT> &>(&bacs_circuit<FieldT>::add_gate), py::arg("g"))
        .def("add_gate", py::overload_cast<const bacs_gate<FieldT> &, const std::string &>(&bacs_circuit<FieldT>::add_gate), py::arg("g"), py::arg("annotation"))
        .def(
            "__eq__", [](bacs_circuit<FieldT> const &self, bacs_circuit<FieldT> const &other) { return self == other; }, py::is_operator())
        .def("print", &bacs_circuit<FieldT>::print)
        .def("print_info", &bacs_circuit<FieldT>::print_info)
        .def("__ostr__", [](bacs_circuit<FieldT> const &self) {
            std::ostringstream os;
            os << self.primary_input_size << "\n";
            os << self.auxiliary_input_size << "\n";
            libff::operator<<(os, self.gates);
            os << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](bacs_circuit<FieldT> &self) {
            std::istringstream os;
            os >> self.primary_input_size;
            libff::consume_newline(os);
            os >> self.auxiliary_input_size;
            libff::consume_newline(os);
            libff::operator>>(os, self.gates);
            libff::consume_OUTPUT_NEWLINE(os);
            return os;
        });
}