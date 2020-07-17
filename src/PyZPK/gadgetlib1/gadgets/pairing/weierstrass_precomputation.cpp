#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/pairing/weierstrass_precomputation.hpp>
#include <libsnark/gadgetlib1/gadgets/pairing/mnt_pairing_params.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for pairing precomputation gadgets.
// The gadgets verify correct precomputation of values for the G1 and G2 variables.

// It only holds values.
void declare_G1_precomputation(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G1_precomputation<ppT>>(m, "G1_precomputation")
        .def(py::init<>())
        .def(py::init<protoboard<FieldT> &,
                      const libff::G1<other_curve<ppT>> &,
                      const std::string &>());
}

// Gadget that verifies correct precomputation of the G1 variable.
void declare_precompute_G1_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<precompute_G1_gadget<ppT>, gadget<FieldT>>(m, "precompute_G1_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_variable<ppT> &,
                      G1_precomputation<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &precompute_G1_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &precompute_G1_gadget<ppT>::generate_r1cs_witness);
}

// G2 Precomputation
void declare_precompute_G2_gadget_coeffs(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<precompute_G2_gadget_coeffs<ppT>>(m, "precompute_G2_gadget_coeffs")
        .def(py::init<>())
        .def(py::init<protoboard<FieldT> &,
                      const std::string &>())
        .def(py::init<protoboard<FieldT> &,
                      const G2_variable<ppT> &,
                      const std::string &>());
}

void declare_G2_precomputation(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G2_precomputation<ppT>>(m, "G2_precomputation")
        .def(py::init<>())
        .def(py::init<protoboard<FieldT> &,
                      const libff::G2<other_curve<ppT>> &,
                      const std::string &>());
}

void declare_precompute_G2_gadget_doubling_step(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<precompute_G2_gadget_doubling_step<ppT>, gadget<FieldT>>(m, "precompute_G2_gadget_doubling_step")
        .def(py::init<protoboard<FieldT> &,
                      const precompute_G2_gadget_coeffs<ppT> &,
                      const precompute_G2_gadget_coeffs<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &precompute_G2_gadget_doubling_step<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &precompute_G2_gadget_doubling_step<ppT>::generate_r1cs_witness);
}

void declare_precompute_G2_gadget_addition_step(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<precompute_G2_gadget_addition_step<ppT>, gadget<FieldT>>(m, "precompute_G2_gadget_addition_step")
        .def(py::init<protoboard<FieldT> &,
                      const bool,
                      const precompute_G2_gadget_coeffs<ppT> &,
                      const precompute_G2_gadget_coeffs<ppT> &,
                      const G2_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &precompute_G2_gadget_addition_step<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &precompute_G2_gadget_addition_step<ppT>::generate_r1cs_witness);
}

// Gadget that verifies correct precomputation of the G2 variable.
void declare_precompute_G2_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<precompute_G2_gadget<ppT>, gadget<FieldT>>(m, "precompute_G2_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G2_variable<ppT> &,
                      G2_precomputation<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &precompute_G2_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &precompute_G2_gadget<ppT>::generate_r1cs_witness);
}

void init_gadgetlib1_pairing_weierstrass_precomputation(py::module &m)
{
    declare_G1_precomputation(m);
    declare_precompute_G1_gadget(m);
    declare_precompute_G2_gadget_coeffs(m);
    declare_G2_precomputation(m);
    declare_precompute_G2_gadget_doubling_step(m);
    declare_precompute_G2_gadget_addition_step(m);
    declare_precompute_G2_gadget(m);
}