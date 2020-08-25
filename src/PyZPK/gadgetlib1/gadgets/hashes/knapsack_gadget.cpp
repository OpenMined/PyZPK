#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/knapsack/knapsack_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  The gadget checks the correct execution of a knapsack (modular subset-sum) over
//  the field specified in the template parameter. With suitable choices of parameters
//  such knapsacks are collision-resistant hashes (CRHs).
//  Given two positive integers m (the input length) and d (the dimension),
//  and a matrix M over the field F and of dimension dxm, the hash H_M maps {0,1}^m
//  to F^d by sending x to M*x. Security of the function (very roughly) depends on
//  d*log(|F|).
//  Below, we give two different gadgets:
//  - knapsack_CRH_with_field_out_gadget, which verifies H_M
//  - knapsack_CRH_with_bit_out_gadget, which verifies H_M when its output is "expanded" to bits.
//  In both cases, a method ("sample_randomness") allows to sample M.
//  The parameter d (the dimension) is fixed at compile time in the struct
//  knapsack_dimension below. The parameter m (the input length) can be chosen
//  at run time (in either gadget).

// Choice of dimension
// The size of FieldT should be (approximately) at least 200 bits
void declare_knapsack_dimension(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<knapsack_dimension<FieldT>>(m, "knapsack_dimension")
        .attr("dimension") = 1;
}

// Knapsack with field output
void declare_knapsack_CRH_with_field_out_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<knapsack_CRH_with_field_out_gadget<FieldT>, gadget<FieldT>>(m, "knapsack_CRH_with_field_out_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const block_variable<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &knapsack_CRH_with_field_out_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &knapsack_CRH_with_field_out_gadget<FieldT>::generate_r1cs_witness)
        .def_static("get_digest_len", &knapsack_CRH_with_field_out_gadget<FieldT>::get_digest_len)
        .def_static("get_block_len", &knapsack_CRH_with_field_out_gadget<FieldT>::get_block_len)
        .def_static("get_hash", &knapsack_CRH_with_field_out_gadget<FieldT>::get_hash, py::arg("input"))
        .def_static("sample_randomness", &knapsack_CRH_with_field_out_gadget<FieldT>::sample_randomness, py::arg("input_len"));
}

// Knapsack with binary output
void declare_knapsack_CRH_with_bit_out_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<knapsack_CRH_with_bit_out_gadget<FieldT>, gadget<FieldT>>(m, "knapsack_CRH_with_bit_out_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const block_variable<FieldT> &,
                      const digest_variable<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &knapsack_CRH_with_bit_out_gadget<FieldT>::generate_r1cs_constraints, py::arg("enforce_bitness"))
        .def("generate_r1cs_witness", &knapsack_CRH_with_bit_out_gadget<FieldT>::generate_r1cs_witness)
        .def_static("get_digest_len", &knapsack_CRH_with_bit_out_gadget<FieldT>::get_digest_len)
        .def_static("get_block_len", &knapsack_CRH_with_bit_out_gadget<FieldT>::get_block_len)
        .def_static("get_hash", &knapsack_CRH_with_bit_out_gadget<FieldT>::get_hash, py::arg("input"))
        .def_static("sample_randomness", &knapsack_CRH_with_bit_out_gadget<FieldT>::sample_randomness, py::arg("input_len"));
}

void init_gadgetlib1_hashes_knapsack_gadget(py::module &m)
{
    declare_knapsack_dimension(m);
    declare_knapsack_CRH_with_field_out_gadget(m);
    declare_knapsack_CRH_with_bit_out_gadget(m);
}