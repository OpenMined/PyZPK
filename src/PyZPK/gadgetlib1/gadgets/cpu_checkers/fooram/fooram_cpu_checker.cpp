#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/fooram/fooram_cpu_checker.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for the FOORAM CPU checker gadget.
// The gadget checks the correct operation for the CPU of the FOORAM architecture.
// In FOORAM, the only instruction is FOO(x) and its encoding is x.
// The instruction FOO(x) has the following semantics:
// - if x is odd: reg <- [2*x+(pc+1)]
// - if x is even: [pc+x] <- reg+pc
// - increment pc by 1
// Starting from empty memory, FOORAM performs non-trivial pseudo-random computation
// that exercises both loads, stores, and instruction fetches.

void init_gadgetlib1_fooram_cpu_checker(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<fooram_cpu_checker<FieldT>, fooram_gadget<FieldT>>(m, "fooram_cpu_checker")
        .def(py::init<fooram_protoboard<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable_array<FieldT> &,
                       pb_variable<FieldT> &,
                       const std::string &>())
        .def("generate_r1cs_constraints", &fooram_cpu_checker<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &fooram_cpu_checker<FieldT>::generate_r1cs_witness)
        .def("generate_r1cs_witness_address", &fooram_cpu_checker<FieldT>::generate_r1cs_witness_address)
        .def("generate_r1cs_witness_other", &fooram_cpu_checker<FieldT>::generate_r1cs_witness_other, py::arg("aux_it"), py::arg("aux_end"))
        .def("dump", &fooram_cpu_checker<FieldT>::dump);
}
