#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libsnark/relations/circuit_satisfaction_problems/tbcs/tbcs.hpp>

namespace py = pybind11;
using namespace libsnark;

// Interfaces for a TBCS gate, a TBCS variable assignment, and a TBCS circuit.
void init_relations_circuit_satisfaction_problems_tbcs(py::module &m)
{
    // Types of TBCS gates (2-input boolean gates).
    // Note that each gate's truth table is encoded in its 4-bit opcode. Namely,
    // if g(X,Y) denotes the output of gate g with inputs X and Y, then
    // OPCODE(g) = (g(0,0),g(0,1),g(1,0),g(1,1))
    // For example, if g is of type IF_X_THEN_Y, which has opcode 13, then the
    // truth table of g is 1101 (13 in binary).
    // (Note that MSB above is g(0,0) and LSB is g(1,1))

    py::enum_<tbcs_gate_type>(m, "tbcs_gate_type", py::arithmetic(), "tbcs_gate_type enumeration")
        .value("TBCS_GATE_CONSTANT_0", TBCS_GATE_CONSTANT_0)
        .value("TBCS_GATE_AND", TBCS_GATE_AND)
        .value("TBCS_GATE_X_AND_NOT_Y", TBCS_GATE_X_AND_NOT_Y)
        .value("TBCS_GATE_X", TBCS_GATE_X)
        .value("TBCS_GATE_NOT_X_AND_Y", TBCS_GATE_NOT_X_AND_Y)
        .value("TBCS_GATE_Y", TBCS_GATE_Y)
        .value("TBCS_GATE_XOR", TBCS_GATE_XOR)
        .value("TBCS_GATE_OR", TBCS_GATE_OR)
        .value("TBCS_GATE_NOR", TBCS_GATE_NOR)
        .value("TBCS_GATE_EQUIVALENCE", TBCS_GATE_EQUIVALENCE)
        .value("TBCS_GATE_NOT_Y", TBCS_GATE_NOT_Y)
        .value("TBCS_GATE_IF_Y_THEN_X", TBCS_GATE_IF_Y_THEN_X)
        .value("TBCS_GATE_NOT_X", TBCS_GATE_NOT_X)
        .value("TBCS_GATE_IF_X_THEN_Y", TBCS_GATE_IF_X_THEN_Y)
        .value("TBCS_GATE_NAND", TBCS_GATE_NAND)
        .value("TBCS_GATE_CONSTANT_1", TBCS_GATE_CONSTANT_1);

    // A TBCS gate is a formal expression of the form
    // g(left_wire,right_wire) = output ,
    // where 'left_wire' and 'right_wire' are the two input wires, and 'output' is
    // the output wire. In other words, a TBCS gate is a 2-input boolean gate;
    // there are 16 possible such gates.
    // A TBCS gate is used to construct a TBCS circuit.

    py::class_<tbcs_gate>(m, "tbcs_gate")
        .def(py::init<>())
        .def_readwrite("left_wire", &tbcs_gate::left_wire)
        .def_readwrite("right_wire", &tbcs_gate::right_wire)
        .def_readwrite("type", &tbcs_gate::type)
        .def_readwrite("output", &tbcs_gate::output)
        .def_readwrite("is_circuit_output", &tbcs_gate::is_circuit_output)
        .def("evaluate", &tbcs_gate::evaluate, py::arg("input"))
        .def("print", &tbcs_gate::print, py::arg("variable_annotations"))
        .def(
            "__eq__", [](tbcs_gate const &self, tbcs_gate const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](tbcs_gate const &self) {
            std::ostringstream os;
            os << self.left_wire << "\n";
            os << self.right_wire << "\n";
            os << (int)self.type << "\n";
            os << self.output << "\n";
            libff::output_bool(os, self.is_circuit_output);
            return os;
        })
        .def("__istr__", [](tbcs_gate &self) {
            std::istringstream os;
            os >> self.left_wire;
            libff::consume_newline(os);
            os >> self.right_wire;
            libff::consume_newline(os);
            int tmp;
            os >> tmp;
            self.type = (tbcs_gate_type)tmp;
            libff::consume_newline(os);
            os >> self.output;
            libff::input_bool(os, self.is_circuit_output);
            return os;
        });

    // A TBCS circuit is a boolean circuit in which every gate has 2 inputs.
    // A TBCS circuit is satisfied by a TBCS variable assignment if every output
    // evaluates to zero.
    // The 0-th variable (i.e., "x_{0}") always represents the constant 1.
    // Thus, the 0-th variable is not included in num_variables.

    py::class_<tbcs_circuit>(m, "tbcs_circuit")
        .def(py::init<>())
        .def_readwrite("primary_input_size", &tbcs_circuit::primary_input_size)
        .def_readwrite("auxiliary_input_size", &tbcs_circuit::auxiliary_input_size)
        .def_readwrite("gates", &tbcs_circuit::gates)
        .def("num_inputs", &tbcs_circuit::num_inputs)
        .def("num_gates", &tbcs_circuit::num_gates)
        .def("num_wires", &tbcs_circuit::num_wires)
        .def("wire_depths", &tbcs_circuit::wire_depths)
        .def("depth", &tbcs_circuit::depth)
        .def("is_valid", &tbcs_circuit::is_valid)
        .def("is_satisfied", &tbcs_circuit::is_satisfied, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def("get_all_wires", &tbcs_circuit::get_all_wires, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def("get_all_outputs", &tbcs_circuit::get_all_outputs, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def("add_gate", py::overload_cast<const tbcs_gate &>(&tbcs_circuit::add_gate), py::arg("g"))
        .def("add_gate", py::overload_cast<const tbcs_gate &, const std::string &>(&tbcs_circuit::add_gate), py::arg("g"), py::arg("annotation"))
        .def(
            "__eq__", [](tbcs_circuit const &self, tbcs_circuit const &other) { return self == other; }, py::is_operator())
        .def("print", &tbcs_circuit::print)
        .def("print_info", &tbcs_circuit::print_info)
        .def("__ostr__", [](tbcs_circuit const &self) {
            std::ostringstream os;
            os << self.primary_input_size << "\n";
            os << self.auxiliary_input_size << "\n";
            libff::operator<<(os, self.gates);
            os << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](tbcs_circuit &self) {
            std::istringstream os;
            os >> self.primary_input_size;
            libff::consume_newline(os);
            os >> self.auxiliary_input_size;
            libff::consume_newline(os);
            libff::operator>>(os, self.gates);
            libff::consume_OUTPUT_NEWLINE(os);
            return os;
        });
    ;
}