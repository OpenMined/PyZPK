#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <vector>
#include <libsnark/relations/ram_computations/rams/tinyram/tinyram_aux.hpp>
#include <libff/common/utils.hpp>
namespace py = pybind11;
using namespace libsnark;

void declare_tinyram_opcode(py::module &m)
{
    py::enum_<tinyram_opcode>(m, "tinyram_opcode", py::arithmetic(), "tinyram_opcode enumeration")
        .value("tinyram_opcode_AND", tinyram_opcode_AND)
        .value("tinyram_opcode_OR", tinyram_opcode_OR)
        .value("tinyram_opcode_XOR", tinyram_opcode_XOR)
        .value("tinyram_opcode_NOT", tinyram_opcode_NOT)
        .value("tinyram_opcode_ADD", tinyram_opcode_ADD)
        .value("tinyram_opcode_SUB", tinyram_opcode_SUB)
        .value("tinyram_opcode_MULL", tinyram_opcode_MULL)
        .value("tinyram_opcode_UMULH", tinyram_opcode_UMULH)
        .value("tinyram_opcode_SMULH", tinyram_opcode_SMULH)
        .value("tinyram_opcode_UDIV", tinyram_opcode_UDIV)
        .value("tinyram_opcode_UMOD", tinyram_opcode_UMOD)
        .value("tinyram_opcode_SHL", tinyram_opcode_SHL)
        .value("tinyram_opcode_SHR", tinyram_opcode_SHR)

        .value("tinyram_opcode_CMPE", tinyram_opcode_CMPE)
        .value("tinyram_opcode_CMPA", tinyram_opcode_CMPA)
        .value("tinyram_opcode_CMPAE", tinyram_opcode_CMPAE)
        .value("tinyram_opcode_CMPG", tinyram_opcode_CMPG)
        .value("tinyram_opcode_CMPGE", tinyram_opcode_CMPGE)

        .value("tinyram_opcode_MOV", tinyram_opcode_MOV)
        .value("tinyram_opcode_CMOV", tinyram_opcode_CMOV)

        .value("tinyram_opcode_JMP", tinyram_opcode_JMP)
        .value("tinyram_opcode_CJMP", tinyram_opcode_CJMP)
        .value("tinyram_opcode_CNJMP", tinyram_opcode_CNJMP)

        .value("tinyram_opcode_10111", tinyram_opcode_10111)
        .value("tinyram_opcode_11000", tinyram_opcode_11000)
        .value("tinyram_opcode_11001", tinyram_opcode_11001)

        .value("tinyram_opcode_STOREB", tinyram_opcode_STOREB)
        .value("tinyram_opcode_LOADB", tinyram_opcode_LOADB)
        .value("tinyram_opcode_STOREW", tinyram_opcode_STOREW)
        .value("tinyram_opcode_LOADW", tinyram_opcode_LOADW)
        .value("tinyram_opcode_READ", tinyram_opcode_READ)
        .value("tinyram_opcode_ANSWER", tinyram_opcode_ANSWER);
}

void declare_tinyram_opcode_args(py::module &m)
{
    py::enum_<tinyram_opcode_args>(m, "tinyram_opcode_args", py::arithmetic(), "tinyram_opcode_args enumeration")
        .value("tinyram_opcode_args_des_arg1_arg2", tinyram_opcode_args_des_arg1_arg2)
        .value("tinyram_opcode_args_des_arg2", tinyram_opcode_args_des_arg2)
        .value("tinyram_opcode_args_arg1_arg2", tinyram_opcode_args_arg1_arg2)
        .value("tinyram_opcode_args_arg2", tinyram_opcode_args_arg2)
        .value("tinyram_opcode_args_none", tinyram_opcode_args_none)
        .value("tinyram_opcode_args_arg2_des", tinyram_opcode_args_arg2_des);
}

void declare_tinyram_architecture_params(py::module &m)
{
    m.def("ensure_tinyram_opcode_value_map", ensure_tinyram_opcode_value_map);

    py::class_<tinyram_program>(m,"tinyram_program");
    py::class_<reg_count_t>(m,"reg_count_t");
    py::class_<reg_width_t>(m,"reg_width_t");

    py::class_<tinyram_input_tape>(m,"tinyram_input_tape");
    py::class_<tinyram_input_tape_iterator>(m,"tinyram_input_tape_iterator");

    py::class_<tinyram_architecture_params>(m, "tinyram_architecture_params")
        .def(py::init<>())
        .def(py::init<const reg_width_t, const reg_count_t>())
        .def_readwrite("w", &tinyram_architecture_params::w, "width of a register")
        .def_readwrite("k", &tinyram_architecture_params::k, "number of registers")
        .def("address_size", &tinyram_architecture_params::address_size)
        .def("value_size", &tinyram_architecture_params::value_size)
        .def("cpu_state_size", &tinyram_architecture_params::cpu_state_size)
        .def("initial_pc_addr", &tinyram_architecture_params::initial_pc_addr)
        .def("initial_cpu_state", &tinyram_architecture_params::initial_cpu_state)
        .def("initial_memory_contents", &tinyram_architecture_params::initial_memory_contents, py::arg("program"), py::arg("primary_input"))
        .def("opcode_width", &tinyram_architecture_params::opcode_width)
        .def("reg_arg_width", &tinyram_architecture_params::reg_arg_width)
        .def("instruction_padding_width", &tinyram_architecture_params::instruction_padding_width)
        .def("reg_arg_or_imm_width", &tinyram_architecture_params::reg_arg_or_imm_width)
        .def("dwaddr_len", &tinyram_architecture_params::dwaddr_len)
        .def("subaddr_len", &tinyram_architecture_params::subaddr_len)
        .def("bytes_in_word", &tinyram_architecture_params::bytes_in_word)
        .def("instr_size", &tinyram_architecture_params::instr_size)
        .def("print", &tinyram_architecture_params::print)
        .def(
            "__eq__", [](tinyram_architecture_params const &self, tinyram_architecture_params const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](tinyram_architecture_params const &self) {
            std::ostringstream os;
            os << self.w << "\n";
            os << self.k << "\n";
            return os;
        })
        .def("__istr__", [](tinyram_architecture_params &self) {
            std::istringstream os;
            os >> self.w;
            libff::consume_newline(os);
            os >> self.k;
            libff::consume_newline(os);
            return os;
        });
}

void init_relations_ram_computations_rams_tinyram(py::module &m)
{
    declare_tinyram_opcode(m);
    declare_tinyram_opcode_args(m);
    declare_tinyram_architecture_params(m);
}