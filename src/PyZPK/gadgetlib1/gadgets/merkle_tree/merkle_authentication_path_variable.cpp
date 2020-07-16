#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/merkle_tree/merkle_authentication_path_variable.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/knapsack/knapsack_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_merkle_authentication_path_variable(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    using HashT =  knapsack_CRH_with_field_out_gadget<FieldT>;

    py::class_<merkle_authentication_path_variable<FieldT, HashT>, gadget<FieldT>>(m, "merkle_authentication_path_variable")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const std::string &>())

        .def_readonly("tree_depth", &merkle_authentication_path_variable<FieldT, HashT>::tree_depth)
        .def("generate_r1cs_constraints", &merkle_authentication_path_variable<FieldT, HashT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &merkle_authentication_path_variable<FieldT, HashT>::generate_r1cs_witness)
        .def("get_authentication_path", &merkle_authentication_path_variable<FieldT, HashT>::get_authentication_path);
}