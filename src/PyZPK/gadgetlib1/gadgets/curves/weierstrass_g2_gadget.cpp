#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/curves/weierstrass_g2_gadget.hpp>
#include <libsnark/gadgetlib1/gadgets/pairing/mnt_pairing_params.hpp>


namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for G2 gadgets.
// The gadgets verify curve arithmetic in G2 = E'(F) where E'/F^e: y^2 = x^3 + A' * X + B'
// is an elliptic curve over F^e in short Weierstrass form.

// Gadget that represents a G2 variable.
void declare_G2_variable(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G2_variable<ppT>, gadget<FieldT>>(m, "G2_variable")
        .def(py::init<protoboard<FieldT> &,
                const std::string &>())
        .def(py::init<protoboard<FieldT> &,
                const libff::G2<other_curve<ppT> > &,
                const std::string &>())
        .def("num_variables", &G2_variable<ppT>::num_variables)
        .def("generate_r1cs_witness", &G2_variable<ppT>::generate_r1cs_witness);
}

// Gadget that creates constraints for the validity of a G2 variable.
void declare_G2_checker_gadget(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<G2_checker_gadget<ppT>, gadget<FieldT>>(m, "G2_checker_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const G2_variable<ppT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &G2_checker_gadget<ppT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &G2_checker_gadget<ppT>::generate_r1cs_witness);
}

void init_gadgetlib1_curves_weierstrass_g2_gadget(py::module &m)
{
    declare_G2_variable(m);
    declare_G2_checker_gadget(m);
}