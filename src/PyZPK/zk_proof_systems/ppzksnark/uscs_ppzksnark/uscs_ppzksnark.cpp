#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/uscs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/uscs_ppzksnark/uscs_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a ppzkSNARK for USCS.

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

void declare_uscs_ppzksnark_proving_key(py::module &m)
{
    // A proving key for the USCS ppzkSNARK.
    using ppT = default_uscs_ppzksnark_pp;

    py::class_<uscs_ppzksnark_proving_key<ppT>>(m, "uscs_ppzksnark_proving_key")
        .def(py::init<>())
        .def(py::init<const uscs_ppzksnark_proving_key<ppT> &>())
        .def("G1_size", &uscs_ppzksnark_proving_key<ppT>::G1_size)
        .def("G2_size", &uscs_ppzksnark_proving_key<ppT>::G2_size)
        .def("G1_sparse_size", &uscs_ppzksnark_proving_key<ppT>::G1_sparse_size)
        .def("G2_sparse_size", &uscs_ppzksnark_proving_key<ppT>::G2_sparse_size)
        .def("size_in_bits", &uscs_ppzksnark_proving_key<ppT>::size_in_bits)
        .def("print_size", &uscs_ppzksnark_proving_key<ppT>::print_size)
        .def(
            "__eq__", [](uscs_ppzksnark_proving_key<ppT> const &self, uscs_ppzksnark_proving_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](uscs_ppzksnark_proving_key<ppT> const &pk) {
            std::ostringstream os;
            os << pk.V_g1_query;
            os << pk.alpha_V_g1_query;
            os << pk.H_g1_query;
            os << pk.V_g2_query;
            os << pk.constraint_system;
            return os;
        })
        .def("__istr__", [](uscs_ppzksnark_proving_key<ppT> &pk) {
            std::istringstream in;
            in >> pk.V_g1_query;
            in >> pk.alpha_V_g1_query;
            in >> pk.H_g1_query;
            in >> pk.V_g2_query;
            in >> pk.constraint_system;
            return in;
        });
}

void declare_uscs_ppzksnark_verification_key(py::module &m)
{
    // A verification key for the USCS ppzkSNARK.
    using ppT = default_uscs_ppzksnark_pp;

    py::class_<uscs_ppzksnark_verification_key<ppT>>(m, "uscs_ppzksnark_verification_key")
        .def(py::init<>())
        .def(py::init<const libff::G2<ppT> &,
                      const libff::G2<ppT> &,
                      const libff::G2<ppT> &,
                      const accumulation_vector<libff::G1<ppT>> &>())
        .def("G1_size", &uscs_ppzksnark_verification_key<ppT>::G1_size)
        .def("G2_size", &uscs_ppzksnark_verification_key<ppT>::G2_size)
        .def("size_in_bits", &uscs_ppzksnark_verification_key<ppT>::size_in_bits)
        .def("print_size", &uscs_ppzksnark_verification_key<ppT>::print_size)
        .def(
            "__eq__", [](uscs_ppzksnark_verification_key<ppT> const &self, uscs_ppzksnark_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](uscs_ppzksnark_verification_key<ppT> const &vk) {
            std::ostringstream os;
            os << vk.tilde_g2 << OUTPUT_NEWLINE;
            os << vk.alpha_tilde_g2 << OUTPUT_NEWLINE;
            os << vk.Z_g2 << OUTPUT_NEWLINE;
            os << vk.encoded_IC_query << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](uscs_ppzksnark_verification_key<ppT> &vk) {
            std::istringstream in;
            in >> vk.tilde_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> vk.alpha_tilde_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> vk.Z_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> vk.encoded_IC_query;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_uscs_ppzksnark_processed_verification_key(py::module &m)
{
    // A verification key for the USCS ppzkSNARK.
    using ppT = default_uscs_ppzksnark_pp;

    py::class_<uscs_ppzksnark_processed_verification_key<ppT>>(m, "uscs_ppzksnark_processed_verification_key")
        .def(py::init<>())
        .def(
            "__eq__", [](uscs_ppzksnark_processed_verification_key<ppT> const &self, uscs_ppzksnark_processed_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](uscs_ppzksnark_processed_verification_key<ppT> const &pvk) {
            std::ostringstream os;
            os << pvk.pp_G1_one_precomp << OUTPUT_NEWLINE;
            os << pvk.pp_G2_one_precomp << OUTPUT_NEWLINE;
            os << pvk.vk_tilde_g2_precomp << OUTPUT_NEWLINE;
            os << pvk.vk_alpha_tilde_g2_precomp << OUTPUT_NEWLINE;
            os << pvk.vk_Z_g2_precomp << OUTPUT_NEWLINE;
            os << pvk.pairing_of_g1_and_g2 << OUTPUT_NEWLINE;
            os << pvk.encoded_IC_query << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](uscs_ppzksnark_processed_verification_key<ppT> &pvk) {
            std::istringstream in;
            in >> pvk.pp_G1_one_precomp;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> pvk.pp_G2_one_precomp;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> pvk.vk_tilde_g2_precomp;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> pvk.vk_alpha_tilde_g2_precomp;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> pvk.vk_Z_g2_precomp;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> pvk.pairing_of_g1_and_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> pvk.encoded_IC_query;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_uscs_ppzksnark_keypair(py::module &m)
{
    // A key pair for the USCS ppzkSNARK, which consists of a proving key and a verification key.
    using ppT = default_uscs_ppzksnark_pp;

    py::class_<uscs_ppzksnark_keypair<ppT>>(m, "uscs_ppzksnark_keypair")
        .def(py::init<>());
}

void declare_uscs_ppzksnark_proof(py::module &m)
{
    // A verification key for the USCS ppzkSNARK.
    using ppT = default_uscs_ppzksnark_pp;

    py::class_<uscs_ppzksnark_proof<ppT>>(m, "uscs_ppzksnark_proof")
        .def(py::init<>())
        .def("G1_size", &uscs_ppzksnark_proof<ppT>::G1_size)
        .def("G2_size", &uscs_ppzksnark_proof<ppT>::G2_size)
        .def("size_in_bits", &uscs_ppzksnark_proof<ppT>::size_in_bits)
        .def("print_size", &uscs_ppzksnark_proof<ppT>::print_size)
        .def("is_well_formed", &uscs_ppzksnark_proof<ppT>::is_well_formed)
        .def(
            "__eq__", [](uscs_ppzksnark_proof<ppT> const &self, uscs_ppzksnark_proof<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](uscs_ppzksnark_proof<ppT> const &proof) {
            std::ostringstream os;
            os << proof.V_g1 << OUTPUT_NEWLINE;
            os << proof.alpha_V_g1 << OUTPUT_NEWLINE;
            os << proof.H_g1 << OUTPUT_NEWLINE;
            os << proof.V_g2 << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](uscs_ppzksnark_proof<ppT> &proof) {
            std::istringstream in;
            in >> proof.V_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> proof.alpha_V_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> proof.H_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> proof.V_g2;
            libff::consume_OUTPUT_NEWLINE(in);

            return in;
        });
}

void declare_USCS_Main_Algorithms(py::module &m)
{
    using ppT = default_uscs_ppzksnark_pp;

    m.def("uscs_ppzksnark_generator", &uscs_ppzksnark_generator<ppT>, R"(A generator algorithm for the USCS ppzkSNARK.
    // Given a USCS constraint system CS, this algorithm produces proving and verification keys for CS.)",
          py::arg("uscs_ppzksnark_constraint_system"));

    m.def("uscs_ppzksnark_prover", &uscs_ppzksnark_prover<ppT>, "A prover algorithm for the USCS ppzkSNARK.", py::arg("uscs_ppzksnark_proving_key"), py::arg("primary_input"), py::arg("auxiliary_input"));

    m.def("uscs_ppzksnark_verifier_weak_IC", &uscs_ppzksnark_verifier_weak_IC<ppT>, R"(A verifier algorithm for the USCS ppzkSNARK that:
    (1) accepts a non-processed verification key, and (2) has weak input consistency.)",
          py::arg("uscs_ppzksnark_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("uscs_ppzksnark_verifier_strong_IC", &uscs_ppzksnark_verifier_strong_IC<ppT>, R"(A verifier algorithm for the USCS ppzkSNARK that:
    (1) accepts a non-processed verification key, and (2) has strong input consistency.)",
          py::arg("uscs_ppzksnark_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("uscs_ppzksnark_verifier_process_vk", &uscs_ppzksnark_verifier_process_vk<ppT>, "Convert a (non-processed) verification key into a processed verification key.", py::arg("uscs_ppzksnark_verification_key"));

    m.def("uscs_ppzksnark_online_verifier_weak_IC", &uscs_ppzksnark_online_verifier_weak_IC<ppT>, R"(A verifier algorithm for the USCS ppzkSNARK that:
    (1) accepts a processed verification key, and (2) has weak input consistency.)",
          py::arg("uscs_ppzksnark_processed_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("uscs_ppzksnark_online_verifier_strong_IC", &uscs_ppzksnark_online_verifier_strong_IC<ppT>, R"(A verifier algorithm for the USCS ppzkSNARK that:
    (1) accepts a processed verification key, and (2) has strong input consistency.)",
          py::arg("uscs_ppzksnark_processed_verification_key"), py::arg("primary_input"), py::arg("proof"));
}

void init_zk_proof_systems_ppzksnark_uscs_ppzksnark_uscs_ppzksnark(py::module &m)
{
    declare_uscs_ppzksnark_proving_key(m);
    declare_uscs_ppzksnark_verification_key(m);
    declare_uscs_ppzksnark_processed_verification_key(m);
    declare_uscs_ppzksnark_keypair(m);
    declare_uscs_ppzksnark_proof(m);
    declare_USCS_Main_Algorithms(m);
}