#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/merkle_tree/merkle_tree_check_update_gadget.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/knapsack/knapsack_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for the Merkle tree check update gadget.
//  The gadget checks the following: given two roots R1 and R2, address A, two
//  values V1 and V2, and authentication path P, check that
//  - P is a valid authentication path for the value V1 as the A-th leaf in a Merkle tree with root R1, and
//  - P is a valid authentication path for the value V2 as the A-th leaf in a Merkle tree with root R2.

void init_merkle_tree_check_update_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    using HashT = knapsack_CRH_with_field_out_gadget<FieldT>;

    py::class_<merkle_tree_check_update_gadget<FieldT, HashT>, gadget<FieldT>>(m, "merkle_tree_check_update_gadget")
        .def_readonly("digest_size", &merkle_tree_check_update_gadget<FieldT, HashT>::digest_size)
        .def_readonly("tree_depth", &merkle_tree_check_update_gadget<FieldT, HashT>::tree_depth)
        .def("generate_r1cs_witness", &merkle_tree_check_update_gadget<FieldT, HashT>::generate_r1cs_witness)
        .def_static("root_size_in_bits", &merkle_tree_check_update_gadget<FieldT, HashT>::root_size_in_bits);
}