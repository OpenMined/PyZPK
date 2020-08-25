#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/routing/benes_routing_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for the Benes routing gadget.
// The gadget verifies that the outputs are a permutation of the inputs,
// by use of a Benes network.
void init_gadgetlib1_routing_benes_routing_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<benes_routing_gadget<FieldT>, gadget<FieldT>>(m, "benes_routing_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const std::vector<pb_variable_array<FieldT>> &,
                      const std::vector<pb_variable_array<FieldT>> &,
                      const size_t,
                      const std::string &>())
        .def("generate_r1cs_constraints", &benes_routing_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &benes_routing_gadget<FieldT>::generate_r1cs_witness, py::arg("permutation"));
}