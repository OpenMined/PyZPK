#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadget.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/compliance_predicate/cp_handler.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_pcd_params.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for a compliance predicate handler.
//  A compliance predicate handler is a base class for creating compliance predicates.
//  It relies on classes declared in gadgetlib1.

void declare_r1cs_pcd_message_variable(py::module &m)
{
    // A variable to represent an r1cs_pcd_message.

    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<r1cs_pcd_message_variable<FieldT>, gadget<FieldT>>(m, "r1cs_pcd_message_variable")
        .def("update_all_vars", &r1cs_pcd_message_variable<FieldT>::update_all_vars)
        .def("generate_r1cs_witness", &r1cs_pcd_message_variable<FieldT>::generate_r1cs_witness)
        .def("get_message", &r1cs_pcd_message_variable<FieldT>::get_message);
}

void declare_r1cs_pcd_local_data_variable(py::module &m)
{
    // A variable to represent an r1cs_pcd_local_data.

    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<r1cs_pcd_local_data_variable<FieldT>, gadget<FieldT>>(m, "r1cs_pcd_local_data_variable")
        .def(py::init<protoboard<FieldT> &,
                      const std::string &>())
        .def("update_all_vars", &r1cs_pcd_local_data_variable<FieldT>::update_all_vars)
        .def("generate_r1cs_witness", &r1cs_pcd_local_data_variable<FieldT>::generate_r1cs_witness);
}

void declare_compliance_predicate_handler(py::module &m)
{
    // A base class for creating compliance predicates.

    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    using protoboardT = protoboard<FieldT>;

    py::class_<compliance_predicate_handler<FieldT, protoboardT>>(m, "compliance_predicate_handler")
        .def("generate_r1cs_constraints", &compliance_predicate_handler<FieldT, protoboardT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &compliance_predicate_handler<FieldT, protoboardT>::generate_r1cs_witness)
        .def("get_compliance_predicate", &compliance_predicate_handler<FieldT, protoboardT>::get_compliance_predicate)
        .def("get_full_variable_assignment", &compliance_predicate_handler<FieldT, protoboardT>::get_full_variable_assignment)
        .def("get_arity", &compliance_predicate_handler<FieldT, protoboardT>::get_arity)
        .def("get_incoming_message", &compliance_predicate_handler<FieldT, protoboardT>::get_incoming_message)
        .def("get_witness", &compliance_predicate_handler<FieldT, protoboardT>::get_witness);
}

void init_zk_proof_systems_pcd_r1cs_pcd_cp_handler(py::module &m)
{
    declare_r1cs_pcd_message_variable(m);
    declare_r1cs_pcd_local_data_variable(m);
    declare_compliance_predicate_handler(m);
}