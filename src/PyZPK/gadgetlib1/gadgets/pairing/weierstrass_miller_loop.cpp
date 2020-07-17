#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/pairing/weierstrass_miller_loop.hpp>
#include <libsnark/gadgetlib1/gadgets/pairing/mnt_pairing_params.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for gadgets for Miller loops.
//  The gadgets verify computations of (single or multiple simultaneous) Miller loops.

// Gadget for doubling step in the Miller loop.
void declare_mnt_miller_loop_dbl_line_eval(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<mnt_miller_loop_dbl_line_eval<ppT>, gadget<FieldT>>(m, "mnt_miller_loop_dbl_line_eval")
        .def(py::init<protoboard<FieldT> &,
                      const G1_precomputation<ppT> &,
                      const precompute_G2_gadget_coeffs<ppT> &,
                      std::shared_ptr<Fqk_variable<ppT>> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &mnt_miller_loop_dbl_line_eval<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &mnt_miller_loop_dbl_line_eval<ppT>::generate_r1cs_witness);
}

// Gadget for addition step in the Miller loop.
void declare_mnt_miller_loop_add_line_eval(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<mnt_miller_loop_add_line_eval<ppT>, gadget<FieldT>>(m, "mnt_miller_loop_add_line_eval")
        .def(py::init<protoboard<FieldT> &,
                      const bool,
                      const G1_precomputation<ppT> &,
                      const precompute_G2_gadget_coeffs<ppT> &,
                      const G2_variable<ppT> &,
                      std::shared_ptr<Fqk_variable<ppT>> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &mnt_miller_loop_add_line_eval<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &mnt_miller_loop_add_line_eval<ppT>::generate_r1cs_witness);
}

// Gadget for verifying a single Miller loop.
void declare_mnt_miller_loop_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<mnt_miller_loop_gadget<ppT>, gadget<FieldT>>(m, "mnt_miller_loop_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const Fqk_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &mnt_miller_loop_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &mnt_miller_loop_gadget<ppT>::generate_r1cs_witness);
}

// Gadget for verifying a double Miller loop (where the second is inverted).
void declare_mnt_e_over_e_miller_loop_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<mnt_e_over_e_miller_loop_gadget<ppT>, gadget<FieldT>>(m, "mnt_e_over_e_miller_loop_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const Fqk_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &mnt_e_over_e_miller_loop_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &mnt_e_over_e_miller_loop_gadget<ppT>::generate_r1cs_witness);
}

// Gadget for verifying a triple Miller loop (where the third is inverted).
void declare_mnt_e_times_e_over_e_miller_loop_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<mnt_e_times_e_over_e_miller_loop_gadget<ppT>, gadget<FieldT>>(m, "mnt_e_times_e_over_e_miller_loop_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const G1_precomputation<ppT> &,
                      const G2_precomputation<ppT> &,
                      const Fqk_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &mnt_e_times_e_over_e_miller_loop_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &mnt_e_times_e_over_e_miller_loop_gadget<ppT>::generate_r1cs_witness);
}

void init_gadgetlib1_pairing_weierstrass_miller_loop(py::module &m)
{
    declare_mnt_miller_loop_dbl_line_eval(m);
    declare_mnt_miller_loop_add_line_eval(m);
    declare_mnt_miller_loop_gadget(m);
    declare_mnt_e_over_e_miller_loop_gadget(m);
    declare_mnt_e_times_e_over_e_miller_loop_gadget(m);
}