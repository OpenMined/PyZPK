#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_sp_ppzkpcd/sp_pcd_circuits.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//   Declaration of functionality for creating and using the two PCD circuits in
//  a single-predicate PCD construction.

void declare_sp_compliance_step_pcd_circuit_maker(py::module &m)
{
    // A compliance-step PCD circuit.
    // The circuit is an R1CS that checks compliance (for the given compliance predicate) and validity of previous proofs.
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<sp_compliance_step_pcd_circuit_maker<ppT>>(m, "sp_compliance_step_pcd_circuit_maker")
        .def(py::init<const r1cs_pcd_compliance_predicate<FieldT> &>())
        .def("generate_r1cs_constraints", &sp_compliance_step_pcd_circuit_maker<ppT>::generate_r1cs_constraints)
        .def("get_circuit", &sp_compliance_step_pcd_circuit_maker<ppT>::get_circuit)
        .def("get_primary_input", &sp_compliance_step_pcd_circuit_maker<ppT>::get_primary_input)
        .def("get_auxiliary_input", &sp_compliance_step_pcd_circuit_maker<ppT>::get_auxiliary_input)
        .def("field_logsize", &sp_compliance_step_pcd_circuit_maker<ppT>::field_logsize)
        .def("field_capacity", &sp_compliance_step_pcd_circuit_maker<ppT>::field_capacity)
        .def("input_size_in_elts", &sp_compliance_step_pcd_circuit_maker<ppT>::input_size_in_elts)
        .def("input_capacity_in_bits", &sp_compliance_step_pcd_circuit_maker<ppT>::input_capacity_in_bits)
        .def("input_size_in_bits", &sp_compliance_step_pcd_circuit_maker<ppT>::input_size_in_bits);
}

void declare_sp_translation_step_pcd_circuit_maker(py::module &m)
{
    // A compliance-step PCD circuit.
    // The circuit is an R1CS that checks compliance (for the given compliance predicate) and validity of previous proofs.
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<sp_translation_step_pcd_circuit_maker<ppT>>(m, "sp_translation_step_pcd_circuit_maker")
        .def(py::init<const r1cs_ppzksnark_verification_key<other_curve<ppT> > &>())
        .def("generate_r1cs_constraints", &sp_translation_step_pcd_circuit_maker<ppT>::generate_r1cs_constraints)
        .def("get_circuit", &sp_translation_step_pcd_circuit_maker<ppT>::get_circuit)
        .def("generate_r1cs_witness", &sp_translation_step_pcd_circuit_maker<ppT>::generate_r1cs_witness)
        .def("get_primary_input", &sp_translation_step_pcd_circuit_maker<ppT>::get_primary_input)
        .def("get_auxiliary_input", &sp_translation_step_pcd_circuit_maker<ppT>::get_auxiliary_input)
        .def("field_logsize", &sp_translation_step_pcd_circuit_maker<ppT>::field_logsize)
        .def("field_capacity", &sp_translation_step_pcd_circuit_maker<ppT>::field_capacity)
        .def("input_size_in_elts", &sp_translation_step_pcd_circuit_maker<ppT>::input_size_in_elts)
        .def("input_capacity_in_bits", &sp_translation_step_pcd_circuit_maker<ppT>::input_capacity_in_bits)
        .def("input_size_in_bits", &sp_translation_step_pcd_circuit_maker<ppT>::input_size_in_bits);
}

void init_zk_proof_systems_pcd_r1cs_pcd_r1cs_sp_ppzkpcd_sp_pcd_circuits(py::module &m)
{
    declare_sp_compliance_step_pcd_circuit_maker(m);
    declare_sp_translation_step_pcd_circuit_maker(m);
}