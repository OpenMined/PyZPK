#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/set_commitment/set_commitment_gadget.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/knapsack/knapsack_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_set_commitment_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    using HashT = knapsack_CRH_with_field_out_gadget<FieldT>;

    py::class_<set_commitment_gadget<FieldT, HashT>, gadget<FieldT>>(m, "set_commitment_gadget")
        .def("generate_r1cs_witness", &set_commitment_gadget<FieldT, HashT>::generate_r1cs_witness)
        .def_static("root_size_in_bits", &set_commitment_gadget<FieldT, HashT>::root_size_in_bits);
}