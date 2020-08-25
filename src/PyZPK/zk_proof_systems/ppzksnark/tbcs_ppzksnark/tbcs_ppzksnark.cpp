#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/tbcs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/tbcs_ppzksnark/tbcs_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a ppzkSNARK for TBCS.
//  This includes:
//  - class for proving key
//  - class for verification key
//  - class for processed verification key
//  - class for key pair (proving key & verification key)
//  - class for proof
//  - generator algorithm
//  - prover algorithm
//  - verifier algorithm (with strong or weak input consistency)
//  - online verifier algorithm (with strong or weak input consistency)

void declare_tbcs_ppzksnark_proving_key(py::module &m)
{
    // A proving key for the TBCS ppzkSNARK.
    using ppT = default_tbcs_ppzksnark_pp;

    py::class_<tbcs_ppzksnark_proving_key<ppT>>(m, "tbcs_ppzksnark_proving_key")
        .def(py::init<>())
        .def(py::init<const tbcs_ppzksnark_proving_key<ppT> &>())
        .def(py::init<const tbcs_ppzksnark_circuit &,
                      const uscs_ppzksnark_proving_key<ppT> &>())
        .def("G1_size", &tbcs_ppzksnark_proving_key<ppT>::G1_size)
        .def("G2_size", &tbcs_ppzksnark_proving_key<ppT>::G2_size)
        .def("G1_sparse_size", &tbcs_ppzksnark_proving_key<ppT>::G1_sparse_size)
        .def("G2_sparse_size", &tbcs_ppzksnark_proving_key<ppT>::G2_sparse_size)
        .def("size_in_bits", &tbcs_ppzksnark_proving_key<ppT>::size_in_bits)
        .def("print_size", &tbcs_ppzksnark_proving_key<ppT>::print_size)
        .def(
            "__eq__", [](tbcs_ppzksnark_proving_key<ppT> const &self, tbcs_ppzksnark_proving_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](tbcs_ppzksnark_proving_key<ppT> const &pk) {
            std::ostringstream os;
            os << pk.circuit << OUTPUT_NEWLINE;
            os << pk.uscs_pk << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](tbcs_ppzksnark_proving_key<ppT> &pk) {
            std::istringstream in;
            in >> pk.circuit;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> pk.uscs_pk;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_tbcs_ppzksnark_keypair(py::module &m)
{
    // A key pair for the TBCS ppzkSNARK, which consists of a proving key and a verification key.
    using ppT = default_tbcs_ppzksnark_pp;

    py::class_<tbcs_ppzksnark_keypair<ppT>>(m, "tbcs_ppzksnark_keypair")
        .def(py::init<>())
        .def(py::init<const tbcs_ppzksnark_proving_key<ppT> &,
                      const tbcs_ppzksnark_verification_key<ppT> &>());
}

void declare_TBCS_Main_Algorithms(py::module &m)
{
    using ppT = default_tbcs_ppzksnark_pp;

    m.def("tbcs_ppzksnark_generator", &tbcs_ppzksnark_generator<ppT>, R"(A generator algorithm for the TBCS ppzkSNARK.
    Given a TBCS constraint system CS, this algorithm produces proving and verification keys for CS.)",
          py::arg("tbcs_ppzksnark_circuit"));

    m.def("tbcs_ppzksnark_prover", &tbcs_ppzksnark_prover<ppT>, "A prover algorithm for the TBCS ppzkSNARK.", py::arg("tbcs_ppzksnark_proving_key"), py::arg("primary_input"), py::arg("auxiliary_input"));

    m.def("tbcs_ppzksnark_verifier_weak_IC", &tbcs_ppzksnark_verifier_weak_IC<ppT>, R"(A verifier algorithm for the TBCS ppzkSNARK that:
    (1) accepts a non-processed verification key, and (2) has weak input consistency.)",
          py::arg("tbcs_ppzksnark_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("tbcs_ppzksnark_verifier_strong_IC", &tbcs_ppzksnark_verifier_strong_IC<ppT>, R"(A verifier algorithm for the TBCS ppzkSNARK that:
    (1) accepts a non-processed verification key, and (2) has strong input consistency.)",
          py::arg("tbcs_ppzksnark_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("tbcs_ppzksnark_verifier_process_vk", &tbcs_ppzksnark_verifier_process_vk<ppT>, "Convert a (non-processed) verification key into a processed verification key.", py::arg("tbcs_ppzksnark_verification_key"));

    m.def("tbcs_ppzksnark_online_verifier_weak_IC", &tbcs_ppzksnark_online_verifier_weak_IC<ppT>, R"(A verifier algorithm for the TBCS ppzkSNARK that:
    (1) accepts a processed verification key, and (2) has weak input consistency.)",
          py::arg("tbcs_ppzksnark_processed_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("tbcs_ppzksnark_online_verifier_strong_IC", &tbcs_ppzksnark_online_verifier_strong_IC<ppT>, R"(A verifier algorithm for the TBCS ppzkSNARK that:
    (1) accepts a processed verification key, and (2) has strong input consistency.)",
          py::arg("tbcs_ppzksnark_processed_verification_key"), py::arg("primary_input"), py::arg("proof"));
}

void init_zk_proof_systems_ppzksnark_tbcs_ppzksnark_tbcs_ppzksnark(py::module &m)
{
    declare_tbcs_ppzksnark_proving_key(m);
    declare_tbcs_ppzksnark_keypair(m);
    declare_TBCS_Main_Algorithms(m);
}