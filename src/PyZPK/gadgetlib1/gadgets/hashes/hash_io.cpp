#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/hash_io.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void declare_digest_variable(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<digest_variable<FieldT>, gadget<FieldT>>(m, "digest_variable")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const std::string &>())
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const pb_variable_array<FieldT> &,
                      const pb_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &digest_variable<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &digest_variable<FieldT>::generate_r1cs_witness)
        .def("get_digest", &digest_variable<FieldT>::get_digest);
}

void declare_block_variable(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<block_variable<FieldT>, gadget<FieldT>>(m, "block_variable")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const std::string &>())
        .def(py::init<protoboard<FieldT> &,
                      const std::vector<pb_variable_array<FieldT>> &,
                      const std::string &>())
        .def(py::init<protoboard<FieldT> &,
                      const digest_variable<FieldT> &,
                      const digest_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_witness", &block_variable<FieldT>::generate_r1cs_witness)
        .def("get_block", &block_variable<FieldT>::get_block);
}

void init_gadgetlib1_hashes_hash_io(py::module &m)
{
    declare_digest_variable(m);
    declare_block_variable(m);
}