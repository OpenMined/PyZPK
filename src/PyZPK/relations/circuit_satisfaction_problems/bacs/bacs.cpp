#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/cast.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <vector>
#include <cassert>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/relations/circuit_satisfaction_problems/bacs/bacs.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

template<typename FieldT>
using bacs_variable_assignment = std::vector<FieldT>;
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
        .def("evaluate", &bacs_gate<FieldT>::evaluate)
        .def("print", &bacs_gate<FieldT>::print)
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
}