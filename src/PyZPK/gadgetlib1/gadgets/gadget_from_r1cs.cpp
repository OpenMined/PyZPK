#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/gadget_from_r1cs.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_gadgetlib1_gadgets_from_r1cs(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<gadget_from_r1cs<FieldT>>(m, "gadget_from_r1cs")
        .def(py::init<protoboard<FieldT> &,
                     const std::vector<pb_variable_array<FieldT> > &,
                     const r1cs_constraint_system<FieldT> &,
                     const std::string &>())
        .def("generate_r1cs_constraints", &gadget_from_r1cs<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &gadget_from_r1cs<FieldT>::generate_r1cs_witness, py::arg("primary_input"), py::arg("auxiliary_input"));
}