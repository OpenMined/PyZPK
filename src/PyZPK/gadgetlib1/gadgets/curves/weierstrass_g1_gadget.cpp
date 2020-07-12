#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/curves/weierstrass_g1_gadget.hpp>
#include <libsnark/gadgetlib1/gadgets/pairing/mnt_pairing_params.hpp>


namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for G1 gadgets.
// The gadgets verify curve arithmetic in G1 = E(F) where E/F: y^2 = x^3 + A * X + B
// is an elliptic curve over F in short Weierstrass form.

// Gadget that represents a G1 variable.
void declare_G1_variable(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G1_variable<ppT>, gadget<FieldT>>(m, "G1_variable")
        .def(py::init<protoboard<FieldT> &,
                const std::string &>())
        .def(py::init<protoboard<FieldT> &,
                const libff::G1<other_curve<ppT> > &,
                const std::string &>())
        .def("num_variables", &G1_variable<ppT>::num_variables)
        .def("generate_r1cs_witness", &G1_variable<ppT>::generate_r1cs_witness);
}

// Gadget that creates constraints for the validity of a G1 variable.
void declare_G1_checker_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G1_checker_gadget<ppT>, gadget<FieldT>>(m, "G1_checker_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &G1_checker_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &G1_checker_gadget<ppT>::generate_r1cs_witness);
}

// Gadget that creates constraints for G1 addition.
void declare_G1_add_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G1_add_gadget<ppT>, gadget<FieldT>>(m, "G1_add_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_variable<ppT> &,
                      const G1_variable<ppT> &,
                      const G1_variable<ppT> &,
                      const std::string &>())
        .def_readwrite("lambda", &G1_add_gadget<ppT>::lambda)
        .def_readwrite("inv", &G1_add_gadget<ppT>::inv)
        .def("generate_r1cs_constraints", &G1_add_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &G1_add_gadget<ppT>::generate_r1cs_witness);
}

// Gadget that creates constraints for G1 doubling.
void declare_G1_dbl_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G1_dbl_gadget<ppT>, gadget<FieldT>>(m, "G1_dbl_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_variable<ppT> &,
                      const G1_variable<ppT> &,
                      const std::string &>())
        .def_readwrite("lambda", &G1_dbl_gadget<ppT>::lambda)
        .def_readwrite("Xsquared", &G1_dbl_gadget<ppT>::Xsquared)
        .def("generate_r1cs_constraints", &G1_dbl_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &G1_dbl_gadget<ppT>::generate_r1cs_witness);
}

// Gadget that creates constraints for G1 multi-scalar multiplication.
void declare_G1_multiscalar_mul_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G1_multiscalar_mul_gadget<ppT>, gadget<FieldT>>(m, "G1_multiscalar_mul_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G1_variable<ppT> &,
                      const pb_variable_array<FieldT> &,
                      const size_t,
                      const std::vector<G1_variable<ppT>> &,
                      const G1_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &G1_multiscalar_mul_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &G1_multiscalar_mul_gadget<ppT>::generate_r1cs_witness);
}

void init_gadgetlib1_curves_weierstrass_g1_gadget(py::module &m)
{
    declare_G1_variable(m);
    declare_G1_checker_gadget(m);
    declare_G1_add_gadget(m);
    declare_G1_dbl_gadget(m);
    declare_G1_multiscalar_mul_gadget(m);
}