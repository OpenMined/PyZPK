#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/fooram/components/bar_gadget.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/fooram/components/fooram_protoboard.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for an auxiliary gadget for the FOORAM CPU.

// The bar gadget checks linear combination Z = aX + bY (mod 2^w) 
// for a, b - const, X, Y - vectors of w bits, where w is implicitly inferred,
// Z - a packed variable. This gadget is used four times in fooram:
// PC' = PC + 1
// load_addr = 2 * x + PC'
// store_addr = x + PC
void declare_bar_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<bar_gadget<FieldT>, gadget<FieldT>>(m, "bar_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const pb_linear_combination_array<FieldT> &,
                      const FieldT &,
                      const pb_linear_combination_array<FieldT> &,
                      const FieldT &,
                      const pb_linear_combination<FieldT> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &bar_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &bar_gadget<FieldT>::generate_r1cs_witness);
}

// Interfaces for a protoboard for the FOORAM CPU.
void declare_fooram_protoboard(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<fooram_protoboard<FieldT>, protoboard<FieldT>>(m, "fooram_protoboard")
        .def(py::init<const fooram_architecture_params &>());
}

void declare_fooram_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<fooram_gadget<FieldT>, gadget<FieldT>>(m, "fooram_gadget")
        .def(py::init<fooram_protoboard<FieldT> &, const std::string &>());
}

void init_gadgetlib1_fooram_components(py::module &m)
{
    declare_bar_gadget(m);
    declare_fooram_protoboard(m);
    declare_fooram_gadget(m);
}