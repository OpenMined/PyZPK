#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/tinyram/components/tinyram_protoboard.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a protoboard for the TinyRAM CPU.
void declare_tinyram_protoboard(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<tinyram_protoboard<FieldT>, protoboard<FieldT>>(m, "tinyram_protoboard")
        .def(py::init<const tinyram_architecture_params &>());
}

void declare_tinyram_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<tinyram_gadget<FieldT>, gadget<FieldT>>(m, "tinyram_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &, const std::string &>());

    py::class_<tinyram_standard_gadget<FieldT>, tinyram_gadget<FieldT>>(m, "tinyram_standard_gadget")
        .def("generate_r1cs_constraints", &tinyram_standard_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &tinyram_standard_gadget<FieldT>::generate_r1cs_witness);
}

void init_gadgetlib1_tinyram_components(py::module &m)
{
    declare_tinyram_protoboard(m);
    declare_tinyram_gadget(m);
}