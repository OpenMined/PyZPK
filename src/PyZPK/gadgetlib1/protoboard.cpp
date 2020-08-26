#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_gadgetlib1_protoboard(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<protoboard<FieldT>>(m, "protoboard")
        .def(py::init<>())
        .def("clear_values", &protoboard<FieldT>::clear_values)
        .def("val", py::overload_cast<const pb_variable<FieldT> &>(&protoboard<FieldT>::val), py::arg("var"))
        .def("val", py::overload_cast<const pb_variable<FieldT> &>(&protoboard<FieldT>::val), py::arg("var"), py::return_value_policy::reference)
        .def("lc_val", py::overload_cast<const pb_linear_combination<FieldT> &>(&protoboard<FieldT>::lc_val), py::arg("lc"))
        .def("lc_val", py::overload_cast<const pb_linear_combination<FieldT> &>(&protoboard<FieldT>::lc_val), py::arg("lc"), py::return_value_policy::reference)
        .def("add_r1cs_constraint", &protoboard<FieldT>::add_r1cs_constraint, py::arg("constr"), py::arg("annotation"))
        .def("augment_variable_annotation", &protoboard<FieldT>::augment_variable_annotation, py::arg("pb_variable"), py::arg("postfix"))
        .def("is_satisfied", &protoboard<FieldT>::is_satisfied)
        .def("num_constraints", &protoboard<FieldT>::num_constraints)
        .def("num_inputs", &protoboard<FieldT>::num_inputs)
        .def("num_variables", &protoboard<FieldT>::num_variables)
        .def("set_input_sizes", &protoboard<FieldT>::set_input_sizes)
        .def("full_variable_assignment", &protoboard<FieldT>::full_variable_assignment)
        .def("primary_input", &protoboard<FieldT>::primary_input)
        .def("auxiliary_input", &protoboard<FieldT>::auxiliary_input)
        .def("get_constraint_system", &protoboard<FieldT>::get_constraint_system)
        .def("set_val", [](protoboard<FieldT> const &self, const pb_variable<FieldT> &var, FieldT &f) {
            self.val(var) = f;
        })
        .def("get_val", [](protoboard<FieldT> const &self, const pb_variable<FieldT> &var) {
            return self.val(var);
        });
}