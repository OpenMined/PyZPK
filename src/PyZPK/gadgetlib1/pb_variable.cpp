#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void declare_pb_variable(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<pb_variable<FieldT>>(m, "pb_variable")
        .def(py::init<const var_index_t>())
        .def("allocate", &pb_variable<FieldT>::allocate, py::arg("protoboard"), py::arg("annotation"));
}

void declare_pb_variable_array(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<pb_variable_array<FieldT>>(m, "pb_variable_array")
        .def(py::init<>())
        .def(py::init<size_t, const pb_variable<FieldT> &>())
        .def("allocate", &pb_variable_array<FieldT>::allocate, py::arg("protoboard"), py::arg("n"), py::arg("annotation"))
        .def("fill_with_field_elements", &pb_variable_array<FieldT>::fill_with_field_elements, py::arg("protoboard"), py::arg("vals"))
        .def("fill_with_bits", &pb_variable_array<FieldT>::fill_with_bits, py::arg("protoboard"), py::arg("bit_vector"))
        .def("fill_with_bits_of_ulong", &pb_variable_array<FieldT>::fill_with_bits_of_ulong, py::arg("protoboard"), py::arg("i"))
        .def("fill_with_bits_of_field_element", &pb_variable_array<FieldT>::fill_with_bits_of_field_element, py::arg("protoboard"), py::arg("Field"))
        .def("get_vals", &pb_variable_array<FieldT>::get_vals, py::arg("protoboard"))
        .def("get_bits", &pb_variable_array<FieldT>::get_bits, py::arg("protoboard"))
        .def("get_field_element_from_bits", &pb_variable_array<FieldT>::get_field_element_from_bits, py::arg("protoboard"));
}

void declare_pb_linear_combination(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<pb_linear_combination<FieldT>>(m, "pb_linear_combination")
        .def(py::init<>())
        .def(py::init<const pb_variable<FieldT> &>())
        .def("assign", &pb_linear_combination<FieldT>::assign, py::arg("protoboard"), py::arg("linear_combination"))
        .def("evaluate", &pb_linear_combination<FieldT>::evaluate, py::arg("protoboard"))
        .def("is_constant", &pb_linear_combination<FieldT>::is_constant)
        .def("constant_term", &pb_linear_combination<FieldT>::constant_term);
}

void declare_pb_linear_combination_array(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<pb_linear_combination_array<FieldT>>(m, "pb_linear_combination_array")
        .def(py::init<>())
        .def(py::init<const pb_variable_array<FieldT> &>())
        .def(py::init<size_t>())
        .def(py::init<size_t, const pb_linear_combination<FieldT> &>())
        .def("evaluate", &pb_linear_combination_array<FieldT>::evaluate, py::arg("protoboard"))
        .def("fill_with_field_elements", &pb_linear_combination_array<FieldT>::fill_with_field_elements, py::arg("protoboard"), py::arg("vals"))
        .def("fill_with_bits", &pb_linear_combination_array<FieldT>::fill_with_bits, py::arg("protoboard"), py::arg("bit_vector"))
        .def("fill_with_bits_of_ulong", &pb_linear_combination_array<FieldT>::fill_with_bits_of_ulong, py::arg("protoboard"), py::arg("i"))
        .def("fill_with_bits_of_field_element", &pb_linear_combination_array<FieldT>::fill_with_bits_of_field_element, py::arg("protoboard"), py::arg("Field"))
        .def("get_vals", &pb_linear_combination_array<FieldT>::get_vals, py::arg("protoboard"))
        .def("get_bits", &pb_linear_combination_array<FieldT>::get_bits, py::arg("protoboard"))
        .def("get_field_element_from_bits", &pb_linear_combination_array<FieldT>::get_field_element_from_bits, py::arg("protoboard"));
}

void init_gadgetlib1_pb_variable(py::module &m)
{
    declare_pb_variable(m);
    declare_pb_variable_array(m);
    declare_pb_linear_combination(m);
    declare_pb_linear_combination_array(m);
}