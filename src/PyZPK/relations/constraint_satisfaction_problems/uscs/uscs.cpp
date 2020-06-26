#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/uscs/uscs.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a USCS constraint, a USCS variable assignment, and a USCS constraint system.
// USCS stands for "Unitary-Square Constraint System".
void init_relations_constraint_satisfaction_problems_uscs(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    py::class_<uscs_constraint_system<FieldT>>(m, "uscs_constraint_system")
        .def(py::init<>())
        .def_readwrite("primary_input_size", &uscs_constraint_system<FieldT>::primary_input_size)
        .def_readwrite("auxiliary_input_size", &uscs_constraint_system<FieldT>::auxiliary_input_size)
        .def_readwrite("constraints", &uscs_constraint_system<FieldT>::constraints)
        .def("num_inputs", &uscs_constraint_system<FieldT>::num_inputs)
        .def("num_variables", &uscs_constraint_system<FieldT>::num_variables)
        .def("num_constraints", &uscs_constraint_system<FieldT>::num_constraints)
        // .def("is_valid", &uscs_constraint_system<FieldT>::is_valid)
        // valid_vector was not declared in this scope of libsnark
        .def("add_constraint", (void (uscs_constraint_system<FieldT>::*)(const uscs_constraint<FieldT> &)) & uscs_constraint_system<FieldT>::add_constraint, py::arg("constraint"))
        .def("add_constraint", (void (uscs_constraint_system<FieldT>::*)(const uscs_constraint<FieldT> &, const std::string &)) & uscs_constraint_system<FieldT>::add_constraint, py::arg("constraint"), py::arg("annotation"))
        .def("is_satisfied", &uscs_constraint_system<FieldT>::is_satisfied, py::arg("primary_input"), py::arg("auxiliary_input"))
        .def(
            "__eq__", [](uscs_constraint_system<FieldT> const &self, uscs_constraint_system<FieldT> const &other) { return self == other; }, py::is_operator())
        .def("report_linear_constraint_statistics", &uscs_constraint_system<FieldT>::report_linear_constraint_statistics)
        .def("__ostr__", [](uscs_constraint_system<FieldT> const &self) {
            std::ostringstream os;
            os << self.primary_input_size << "\n";
            os << self.auxiliary_input_size << "\n";
            os << self.num_constraints() << "\n";
            for (const uscs_constraint<FieldT> &c : self.constraints)
            {
                os << c;
            }
            return os;
        })
        .def("__istr__", [](uscs_constraint_system<FieldT> &self) {
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
                uscs_constraint<FieldT> c;
                os >> c;
                self.constraints.emplace_back(c);
            }
            return os;
        });
}
