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
#include <libsnark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a R1CS constraint, a R1CS variable assignment, and a R1CS constraint system.
void init_relations_constraint_satisfaction_problems_r1cs(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    py::class_<r1cs_constraint<FieldT>>(m, "r1cs_constraint")
        .def(py::init<>())
        .def_readwrite("a", &r1cs_constraint<FieldT>::a)
        .def_readwrite("b", &r1cs_constraint<FieldT>::b)
        .def_readwrite("c", &r1cs_constraint<FieldT>::c)
        .def(py::init<const linear_combination<FieldT> &,
                      const linear_combination<FieldT> &,
                      const linear_combination<FieldT> &>())
        .def(py::init<const std::initializer_list<linear_combination<FieldT>> &,
                      const std::initializer_list<linear_combination<FieldT>> &,
                      const std::initializer_list<linear_combination<FieldT>> &>())
        .def(
            "__eq__", [](r1cs_constraint<FieldT> const &self, r1cs_constraint<FieldT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_constraint<FieldT> const &self) {
            std::ostringstream os;
            os << self.a << "\n";
            os << self.b << "\n";
            os << self.c << "\n";
            return os;
        })
        .def("__istr__", [](r1cs_constraint<FieldT> &self) {
            std::istringstream os;
            os >> self.a;
            os >> self.b;
            os >> self.c;
            return os;
        });

    py::class_<r1cs_constraint_system<FieldT>>(m, "r1cs_constraint_system")
        .def(py::init<>())
        .def_readwrite("primary_input_size", &r1cs_constraint_system<FieldT>::primary_input_size)
        .def_readwrite("auxiliary_input_size", &r1cs_constraint_system<FieldT>::auxiliary_input_size)
        .def_readwrite("constraints", &r1cs_constraint_system<FieldT>::constraints)
        .def("num_inputs", &r1cs_constraint_system<FieldT>::num_inputs)
        .def("num_variables", &r1cs_constraint_system<FieldT>::num_variables)
        .def("num_constraints", &r1cs_constraint_system<FieldT>::num_constraints)
        .def("is_valid", &r1cs_constraint_system<FieldT>::is_valid)
        .def("add_constraint", (void (r1cs_constraint_system<FieldT>::*)(const r1cs_constraint<FieldT> &)) & r1cs_constraint_system<FieldT>::add_constraint, py::arg("c"))
        .def("add_constraint", (void (r1cs_constraint_system<FieldT>::*)(const r1cs_constraint<FieldT> &, const std::string &)) & r1cs_constraint_system<FieldT>::add_constraint, py::arg("c"), py::arg("annotation"))
        .def("is_satisfied", &r1cs_constraint_system<FieldT>::is_satisfied, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def("swap_AB_if_beneficial", &r1cs_constraint_system<FieldT>::swap_AB_if_beneficial)
        .def(
            "__eq__", [](r1cs_constraint_system<FieldT> const &self, r1cs_constraint_system<FieldT> const &other) { return self == other; }, py::is_operator())
        .def("report_linear_constraint_statistics", &r1cs_constraint_system<FieldT>::report_linear_constraint_statistics)
        .def("__ostr__", [](r1cs_constraint_system<FieldT> const &self) {
            std::ostringstream os;
            os << self.primary_input_size << "\n";
            os << self.auxiliary_input_size << "\n";
            for (const r1cs_constraint<FieldT> &c : self.constraints)
            {
                os << c;
            }
            return os;
        })
        .def("__istr__", [](r1cs_constraint_system<FieldT> &self) {
            std::istringstream os;
            os >> self.primary_input_size;
            os >> self.auxiliary_input_size;
            self.constraints.clear();
            size_t s;
            os >> s;
            char b;
            os.read(&b, 1);
            self.constraints.reserve(s);
            for (size_t i = 0; i < s; ++i)
            {
                r1cs_constraint<FieldT> c;
                os >> c;
                self.constraints.emplace_back(c);
            }
            return os;
        });
}