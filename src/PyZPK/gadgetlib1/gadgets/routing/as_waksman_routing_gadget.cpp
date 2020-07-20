#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/routing/as_waksman_routing_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for the AS-Waksman routing gadget.

//  The gadget verifies that the outputs are a permutation of the inputs,
//  by use of an AS-Waksman network.
void init_gadgetlib1_routing_as_waksman_routing_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<as_waksman_routing_gadget<FieldT>, gadget<FieldT>>(m, "as_waksman_routing_gadget")
        .def(py::init<protoboard<FieldT> &,
                      const size_t,
                      const std::vector<pb_variable_array<FieldT>> &,
                      const std::vector<pb_variable_array<FieldT>> &,
                      const std::string &>())
        .def("generate_r1cs_constraints", &as_waksman_routing_gadget<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &as_waksman_routing_gadget<FieldT>::generate_r1cs_witness);
}