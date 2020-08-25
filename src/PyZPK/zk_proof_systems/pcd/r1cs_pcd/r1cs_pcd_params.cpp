#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_pcd_params.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void declare_r1cs_pcd_compliance_predicate_primary_input(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<r1cs_pcd_compliance_predicate_primary_input<FieldT>>(m, "r1cs_pcd_compliance_predicate_primary_input")
        .def(py::init<const std::shared_ptr<r1cs_pcd_message<FieldT>> &>())
        .def("as_r1cs_primary_input", &r1cs_pcd_compliance_predicate_primary_input<FieldT>::as_r1cs_primary_input);
}

void declare_r1cs_pcd_compliance_predicate_auxiliary_input(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<r1cs_pcd_compliance_predicate_auxiliary_input<FieldT>>(m, "r1cs_pcd_compliance_predicate_auxiliary_input")
        .def(py::init<const std::vector<std::shared_ptr<r1cs_pcd_message<FieldT>>> &,
                      const std::shared_ptr<r1cs_pcd_local_data<FieldT>> &,
                      const r1cs_pcd_witness<FieldT> &>())
        .def("as_r1cs_auxiliary_input", &r1cs_pcd_compliance_predicate_auxiliary_input<FieldT>::as_r1cs_auxiliary_input, py::arg("incoming_message_payload_lengths"));
}

void init_zk_proof_systems_pcd_r1cs_pcd_r1cs_pcd_params(py::module &m)
{
    declare_r1cs_pcd_compliance_predicate_primary_input(m);
    declare_r1cs_pcd_compliance_predicate_auxiliary_input(m);
}