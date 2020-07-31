#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadget.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/compliance_predicate/examples/tally_cp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_pcd_params.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for the tally compliance predicate.
//  The tally compliance predicate has two purposes:
//  (1) it exemplifies the use of interfaces declared in cp_handler.hpp, and
//  (2) it enables us to test r1cs_pcd functionalities.

void declare_tally_pcd_message(py::module &m)
{
    // Subclasses a R1CS PCD message to the tally compliance predicate.
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<tally_pcd_message<FieldT>, r1cs_pcd_message<FieldT>>(m, "tally_pcd_message")
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const size_t>())
        .def("payload_as_r1cs_variable_assignment", &tally_pcd_message<FieldT>::payload_as_r1cs_variable_assignment)
        .def("print", &tally_pcd_message<FieldT>::print);
}

void declare_tally_pcd_local_data(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<tally_pcd_local_data<FieldT>, r1cs_pcd_local_data<FieldT>>(m, "tally_pcd_local_data")
        .def(py::init<const size_t>())
        .def("as_r1cs_variable_assignment", &tally_pcd_local_data<FieldT>::as_r1cs_variable_assignment)
        .def("print", &tally_pcd_local_data<FieldT>::print);
}

void declare_tally_cp_handler(py::module &m)
{
    // Subclass a R1CS compliance predicate handler to the tally compliance predicate handler.

    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    using protoboardT = protoboard<FieldT>;

    py::class_<tally_cp_handler<FieldT>, compliance_predicate_handler<FieldT, protoboardT>>(m, "tally_cp_handler")
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const bool,
                      const std::set<size_t>>())
        .def("generate_r1cs_constraints", &tally_cp_handler<FieldT>::generate_r1cs_constraints)
        .def("generate_r1cs_witness", &tally_cp_handler<FieldT>::generate_r1cs_witness)
        .def("get_base_case_message", &tally_cp_handler<FieldT>::get_base_case_message);
}

void init_zk_proof_systems_pcd_r1cs_pcd_tally_cp(py::module &m)
{
    declare_tally_pcd_message(m);
    declare_tally_pcd_local_data(m);
    declare_tally_cp_handler(m);
}