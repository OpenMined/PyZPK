#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void declare_packing_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<packing_gadget<FieldT>>(m, "packing_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &packing_gadget<FieldT>::generate_r1cs_constraints, py::arg("enforce_bitness"))
        .def("generate_r1cs_witness_from_packed", &packing_gadget<FieldT>::generate_r1cs_witness_from_packed)
        .def("generate_r1cs_witness_from_bits", &packing_gadget<FieldT>::generate_r1cs_witness_from_bits);
}

void declare_multipacking_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<multipacking_gadget<FieldT>>(m, "multipacking_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const size_t,
                      const std::string &>())
        .def("generate_r1cs_constraints", &multipacking_gadget<FieldT>::generate_r1cs_constraints, py::arg("enforce_bitness"))
        .def("generate_r1cs_witness_from_packed", &multipacking_gadget<FieldT>::generate_r1cs_witness_from_packed)
        .def("generate_r1cs_witness_from_bits", &multipacking_gadget<FieldT>::generate_r1cs_witness_from_bits);
}

void declare_field_vector_copy_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<field_vector_copy_gadget<FieldT>>(m, "field_vector_copy_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &field_vector_copy_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &field_vector_copy_gadget<FieldT>::generate_r1cs_witness);
}

void declare_bit_vector_copy_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<bit_vector_copy_gadget<FieldT>>(m, "bit_vector_copy_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_variable_array<FieldT> &,
                      const pb_linear_combination<FieldT> &,
                      const size_t,
                      const std::string &>())
        .def("generate_r1cs_constraints", &bit_vector_copy_gadget<FieldT>::generate_r1cs_constraints, py::arg("enforce_source_bitness"), py::arg("enforce_target_bitness"))
        .def("generate_r1cs_witness", &bit_vector_copy_gadget<FieldT>::generate_r1cs_witness);
}

void init_gadgetlib1_gadgets_basic_gadgets(py::module &m)
{
    declare_packing_gadget(m);
    declare_multipacking_gadget(m);
    declare_field_vector_copy_gadget(m);
    declare_bit_vector_copy_gadget(m);
}