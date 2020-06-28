#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <vector>
#include <libsnark/relations/ram_computations/rams/fooram/fooram_params.hpp>
#include <libsnark/relations/ram_computations/rams/fooram/fooram_aux.hpp>
#include <libff/common/utils.hpp>
namespace py = pybind11;
using namespace libsnark;

void init_relations_ram_computations_rams_fooram(py::module &m)
{
    py::class_<fooram_architecture_params>(m, "fooram_architecture_params")
        .def(py::init<const size_t>())
        .def_readwrite("w", &fooram_architecture_params::w)
        .def("num_addresses", &fooram_architecture_params::num_addresses)
        .def("address_size", &fooram_architecture_params::address_size)
        .def("value_size", &fooram_architecture_params::value_size)
        .def("cpu_state_size", &fooram_architecture_params::cpu_state_size)
        .def("initial_pc_addr", &fooram_architecture_params::initial_pc_addr)
        .def("initial_memory_contents", &fooram_architecture_params::initial_memory_contents,
             py::arg("program"), py::arg("primary_input"))
        .def("initial_cpu_state", &fooram_architecture_params::initial_cpu_state)
        .def("print", &fooram_architecture_params::print)
        .def(
            "__eq__", [](fooram_architecture_params const &self, fooram_architecture_params const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](fooram_architecture_params const &self) {
            std::ostringstream os;
            os << self.w << "\n";
            return os;
        })
        .def("__istr__", [](fooram_architecture_params &self) {
            std::istringstream os;
            os >> self.w;
            libff::consume_newline(os);
            return os;
        });
}