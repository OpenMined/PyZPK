#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a ppzkSNARK for R1CS with a security proof
// in the generic group (GG) model.

// This includes:
// - class for proving key
// - class for verification key
// - class for processed verification key
// - class for key pair (proving key & verification key)
// - class for proof
// - generator algorithm
// - prover algorithm
// - verifier algorithm (with strong or weak input consistency)
// - online verifier algorithm (with strong or weak input consistency)

void declare_r1cs_gg_ppzksnark_proving_key(py::module &m)
{
    // A proving key for the R1CS GG-ppzkSNARK.
    using ppT = default_r1cs_gg_ppzksnark_pp;

    py::class_<r1cs_gg_ppzksnark_proving_key<ppT>>(m, "r1cs_gg_ppzksnark_proving_key")
        .def(py::init<>())
        .def(py::init<const r1cs_gg_ppzksnark_proving_key<ppT> &>())
        .def("G1_size", &r1cs_gg_ppzksnark_proving_key<ppT>::G1_size)
        .def("G2_size", &r1cs_gg_ppzksnark_proving_key<ppT>::G2_size)
        .def("G1_sparse_size", &r1cs_gg_ppzksnark_proving_key<ppT>::G1_sparse_size)
        .def("G2_sparse_size", &r1cs_gg_ppzksnark_proving_key<ppT>::G2_sparse_size)
        .def("size_in_bits", &r1cs_gg_ppzksnark_proving_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_gg_ppzksnark_proving_key<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_gg_ppzksnark_proving_key<ppT> const &self, r1cs_gg_ppzksnark_proving_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_gg_ppzksnark_proving_key<ppT> const &self) {
            std::ostringstream os;
            os << self.alpha_g1 << OUTPUT_NEWLINE;
            os << self.beta_g1 << OUTPUT_NEWLINE;
            os << self.beta_g2 << OUTPUT_NEWLINE;
            os << self.delta_g1 << OUTPUT_NEWLINE;
            os << self.delta_g2 << OUTPUT_NEWLINE;
            os << self.A_query;
            os << self.B_query;
            os << self.H_query;
            os << self.L_query;
            os << self.constraint_system;
            return os;
        })
        .def("__istr__", [](r1cs_gg_ppzksnark_proving_key<ppT> &self) {
            std::istringstream in;
            in >> self.alpha_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.beta_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.beta_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.delta_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.delta_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.A_query;
            in >> self.B_query;
            in >> self.H_query;
            in >> self.L_query;
            in >> self.constraint_system;
            return in;
        });
}

void declare_r1cs_gg_ppzksnark_verification_key(py::module &m)
{
    // A verification key for the R1CS GG-ppzkSNARK.
    using ppT = default_r1cs_gg_ppzksnark_pp;

    py::class_<r1cs_gg_ppzksnark_verification_key<ppT>>(m, "r1cs_gg_ppzksnark_verification_key")
        .def(py::init<>())
        .def(py::init<const r1cs_gg_ppzksnark_verification_key<ppT> &>())
        .def("G1_size", &r1cs_gg_ppzksnark_verification_key<ppT>::G1_size)
        .def("G2_size", &r1cs_gg_ppzksnark_verification_key<ppT>::G2_size)
        .def("GT_size", &r1cs_gg_ppzksnark_verification_key<ppT>::GT_size)
        .def("size_in_bits", &r1cs_gg_ppzksnark_verification_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_gg_ppzksnark_verification_key<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_gg_ppzksnark_verification_key<ppT> const &self, r1cs_gg_ppzksnark_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_gg_ppzksnark_verification_key<ppT> const &self) {
            std::ostringstream os;
            os << self.alpha_g1_beta_g2 << OUTPUT_NEWLINE;
            os << self.gamma_g2 << OUTPUT_NEWLINE;
            os << self.delta_g2 << OUTPUT_NEWLINE;
            os << self.gamma_ABC_g1 << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](r1cs_gg_ppzksnark_verification_key<ppT> &self) {
            std::istringstream in;
            in >> self.alpha_g1_beta_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.gamma_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.delta_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.gamma_ABC_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_r1cs_gg_ppzksnark_processed_verification_key(py::module &m)
{
    // A processed verification key for the R1CS GG-ppzkSNARK.
    using ppT = default_r1cs_gg_ppzksnark_pp;

    py::class_<r1cs_gg_ppzksnark_processed_verification_key<ppT>>(m, "r1cs_gg_ppzksnark_processed_verification_key")
        .def(py::init<>())
        .def(
            "__eq__", [](r1cs_gg_ppzksnark_processed_verification_key<ppT> const &self, r1cs_gg_ppzksnark_processed_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_gg_ppzksnark_processed_verification_key<ppT> const &self) {
            std::ostringstream os;
            os << self.vk_alpha_g1_beta_g2 << OUTPUT_NEWLINE;
            os << self.vk_gamma_g2_precomp << OUTPUT_NEWLINE;
            os << self.vk_delta_g2_precomp << OUTPUT_NEWLINE;
            os << self.gamma_ABC_g1 << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](r1cs_gg_ppzksnark_processed_verification_key<ppT> &self) {
            std::istringstream in;
            in >> self.vk_alpha_g1_beta_g2;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.vk_gamma_g2_precomp;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.vk_delta_g2_precomp;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> self.gamma_ABC_g1;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_r1cs_gg_ppzksnark_keypair(py::module &m)
{
    // A key pair for the R1CS GG-ppzkSNARK, which consists of a proving key and a verification key.
    using ppT = default_r1cs_gg_ppzksnark_pp;

    py::class_<r1cs_gg_ppzksnark_keypair<ppT>>(m, "r1cs_gg_ppzksnark_keypair")
        .def(py::init<>())
        .def(py::init<const r1cs_gg_ppzksnark_keypair<ppT> &>());
}

void declare_r1cs_gg_ppzksnark_proof(py::module &m)
{
    // A proof for the R1CS GG-ppzkSNARK.
    using ppT = default_r1cs_gg_ppzksnark_pp;

    py::class_<r1cs_gg_ppzksnark_proof<ppT>>(m, "r1cs_gg_ppzksnark_proof")
        .def(py::init<>())
        .def(py::init<const r1cs_gg_ppzksnark_proof<ppT> &>())
        .def("G1_size", &r1cs_gg_ppzksnark_proof<ppT>::G1_size)
        .def("G2_size", &r1cs_gg_ppzksnark_proof<ppT>::G2_size)
        .def("is_well_formed", &r1cs_gg_ppzksnark_proof<ppT>::is_well_formed)
        .def("size_in_bits", &r1cs_gg_ppzksnark_proof<ppT>::size_in_bits)
        .def("print_size", &r1cs_gg_ppzksnark_proof<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_gg_ppzksnark_proof<ppT> const &self, r1cs_gg_ppzksnark_proof<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_gg_ppzksnark_proof<ppT> const &proof) {
            std::ostringstream os;

            os << proof.g_A << OUTPUT_NEWLINE;
            os << proof.g_B << OUTPUT_NEWLINE;
            os << proof.g_C << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](r1cs_gg_ppzksnark_proof<ppT> &proof) {
            std::istringstream in;
            in >> proof.g_A;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> proof.g_B;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> proof.g_C;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_r1cs_gg_Main_Algorithms(py::module &m)
{
    using ppT = default_r1cs_gg_ppzksnark_pp;

    m.def("r1cs_gg_ppzksnark_generator", &r1cs_gg_ppzksnark_generator<ppT>, R"(A generator algorithm for the R1CS GG-ppzkSNARK.
    Given a R1CS constraint system CS, this algorithm produces proving and verification keys for CS.)",
          py::arg("r1cs_gg_ppzksnark_constraint_system"));

    m.def("r1cs_gg_ppzksnark_prover", &r1cs_gg_ppzksnark_prover<ppT>, "A prover algorithm for the R1CS GG-ppzkSNARK.", py::arg("r1cs_gg_ppzksnark_proving_key"), py::arg("primary_input"), py::arg("auxiliary_input"));

    m.def("r1cs_gg_ppzksnark_verifier_weak_IC", &r1cs_gg_ppzksnark_verifier_weak_IC<ppT>, R"(A verifier algorithm for the R1CS GG-ppzkSNARK that:
    (1) accepts a non-processed verification key, and (2) has weak input consistency.)",
          py::arg("r1cs_gg_ppzksnark_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("r1cs_gg_ppzksnark_verifier_strong_IC", &r1cs_gg_ppzksnark_verifier_strong_IC<ppT>, R"(A verifier algorithm for the R1CS GG-ppzkSNARK that:
    (1) accepts a non-processed verification key, and (2) has strong input consistency.)",
          py::arg("r1cs_gg_ppzksnark_verification_key"), py::arg("primary_input"), py::arg("proof"));

    m.def("r1cs_gg_ppzksnark_verifier_process_vk", &r1cs_gg_ppzksnark_verifier_process_vk<ppT>, R"( Convert a (non-processed) verification key into a processed verification key.)", py::arg("r1cs_gg_ppzksnark_verification_key"));

    m.def("r1cs_gg_ppzksnark_online_verifier_weak_IC", &r1cs_gg_ppzksnark_online_verifier_weak_IC<ppT>, R"(A verifier algorithm for the R1CS GG-ppzkSNARK that:
    (1) accepts a processed verification key, and (2) has weak input consistency.)",
          py::arg("r1cs_gg_ppzksnark_processed_verification_key"), py::arg("input"), py::arg("proof"));

    m.def("r1cs_gg_ppzksnark_online_verifier_strong_IC", &r1cs_gg_ppzksnark_online_verifier_strong_IC<ppT>, R"(A verifier algorithm for the R1CS GG-ppzkSNARK  that:
    (1) accepts a processed verification key, and (2) has strong input consistency.)",
          py::arg("r1cs_gg_ppzksnark_processed_verification_key"), py::arg("primary_input"), py::arg("proof"));
}

void init_zk_proof_systems_ppzksnark_r1cs_gg_ppzksnark_r1cs_gg_ppzksnark(py::module &m)
{
    declare_r1cs_gg_ppzksnark_proving_key(m);
    declare_r1cs_gg_ppzksnark_verification_key(m);
    declare_r1cs_gg_ppzksnark_processed_verification_key(m);
    declare_r1cs_gg_ppzksnark_keypair(m);
    declare_r1cs_gg_ppzksnark_proof(m);
    declare_r1cs_gg_Main_Algorithms(m);
}