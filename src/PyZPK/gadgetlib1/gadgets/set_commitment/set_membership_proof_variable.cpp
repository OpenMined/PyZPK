#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/set_commitment/set_membership_proof_variable.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/knapsack/knapsack_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_set_membership_proof_variable(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    using HashT = knapsack_CRH_with_field_out_gadget<FieldT>;

    py::class_<set_membership_proof_variable<FieldT, HashT>, gadget<FieldT>>(m, "set_membership_proof_variable")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const std::string &>())
        .def_readwrite("address_bits", &set_membership_proof_variable<FieldT, HashT>::address_bits)
        .def_readwrite("merkle_path", &set_membership_proof_variable<FieldT, HashT>::merkle_path)
        .def_readonly("max_entries", &set_membership_proof_variable<FieldT, HashT>::max_entries)
        .def_readonly("tree_depth", &set_membership_proof_variable<FieldT, HashT>::tree_depth)
        .def("generate_r1cs_constraints", &set_membership_proof_variable<FieldT, HashT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &set_membership_proof_variable<FieldT, HashT>::generate_r1cs_witness)
        .def("get_membership_proof", &set_membership_proof_variable<FieldT, HashT>::get_membership_proof)
        .def_static("as_r1cs_variable_assignment", &set_membership_proof_variable<FieldT, HashT>::as_r1cs_variable_assignment);
}