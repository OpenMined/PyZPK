#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/r1cs_ppzkadsnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzkadsnark/r1cs_ppzkadsnark/r1cs_ppzkadsnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Declaration of interfaces for a ppzkADSNARK for R1CS.
//  This includes:
//  - class for authentication key (public and symmetric)
//  - class for authentication verification key (public and symmetric)
//  - class for proving key
//  - class for verification key
//  - class for processed verification key
//  - class for key tuple (authentication key & proving key & verification key)
//  - class for authenticated data
//  - class for proof
//  - generator algorithm
//  - authentication key generator algorithm
//  - prover algorithm
//  - verifier algorithm (public and symmetric)
//  - online verifier algorithm (public and symmetric)
//  The implementation instantiates the construction in \[BBFR15], which in turn
//  is based on the r1cs_ppzkadsnark proof system.

// ppzkADSNARK = "PreProcessing Zero-Knowledge Succinct Non-interactive ARgument of Knowledge Over Authenticated Data"

void declare_r1cs_ppzkadsnark_pub_auth_prms(py::module &m)
{
    // public authentication parameters for the R1CS ppzkADSNARK

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_pub_auth_prms<ppT>>(m, "r1cs_ppzkadsnark_pub_auth_prms")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzkadsnark_pub_auth_prms<ppT> &>())
        .def(
            "__eq__", [](r1cs_ppzkadsnark_pub_auth_prms<ppT> const &self, r1cs_ppzkadsnark_pub_auth_prms<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzkadsnark_pub_auth_prms<ppT> const &self) {
        std::ostringstream os;
        os << self.I1;
        return os;
            })
        .def("__istr__", [](r1cs_ppzkadsnark_pub_auth_prms<ppT> &self) {
                std::istringstream in;
                in >> self.I1;
                return in;
            });
}

void declare_r1cs_ppzkadsnark_sec_auth_key(py::module &m)
{
    // Secret authentication key for the R1CS ppzkADSNARK

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_sec_auth_key<ppT>>(m, "r1cs_ppzkadsnark_sec_auth_key")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzkadsnark_sec_auth_key<ppT> &>());
}

void declare_r1cs_ppzkadsnark_pub_auth_key(py::module &m)
{
    // public authentication Key for the R1CS ppzkADSNARK

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_pub_auth_key<ppT>>(m, "r1cs_ppzkadsnark_pub_auth_key")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzkadsnark_pub_auth_key<ppT> &>());
}

void declare_r1cs_ppzkadsnark_auth_keys(py::module &m)
{
    // Authentication key material

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_auth_keys<ppT>>(m, "r1cs_ppzkadsnark_auth_keys")
        .def(py::init<>());
}

void declare_r1cs_ppzkadsnark_auth_data(py::module &m)
{
    // Authenticated data for the R1CS ppzkADSNARK

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_auth_data<ppT>>(m, "r1cs_ppzkadsnark_auth_data")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzkadsnark_auth_data<ppT> &>())
        .def("__ostr__", [](r1cs_ppzkadsnark_auth_data<ppT> const &self) {
        std::ostringstream os;
        os << self.mu;
        os << self.Lambda;
        return os;
            })
        .def("__istr__", [](r1cs_ppzkadsnark_auth_data<ppT> &self) {
                std::istringstream in;
                in >> self.mu;
                in >> self.Lambda;
                return in;
            });
}

void declare_r1cs_ppzkadsnark_proving_key(py::module &m)
{
    // A proving key for the R1CS ppzkADSNARK.

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_proving_key<ppT>>(m, "r1cs_ppzkadsnark_proving_key")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzkadsnark_proving_key<ppT> &>())
        .def("G1_size", &r1cs_ppzkadsnark_proving_key<ppT>::G1_size)
        .def("G2_size", &r1cs_ppzkadsnark_proving_key<ppT>::G2_size)
        .def("G1_sparse_size", &r1cs_ppzkadsnark_proving_key<ppT>::G1_sparse_size)
        .def("G2_sparse_size", &r1cs_ppzkadsnark_proving_key<ppT>::G2_sparse_size)
        .def("size_in_bits", &r1cs_ppzkadsnark_proving_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_ppzkadsnark_proving_key<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_ppzkadsnark_proving_key<ppT> const &self, r1cs_ppzkadsnark_proving_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzkadsnark_proving_key<ppT> const &self) {
        std::ostringstream os;
        os << self.A_query;
        os << self.B_query;
        os << self.C_query;
        os << self.H_query;
        os << self.K_query;
        os << self.rA_i_Z_g1;
        os << self.constraint_system;
        return os;
            })
        .def("__istr__", [](r1cs_ppzkadsnark_proving_key<ppT> &self) {
                std::istringstream in;
                in >> self.A_query;
                in >> self.B_query;
                in >> self.C_query;
                in >> self.H_query;
                in >> self.K_query;
                in >> self.rA_i_Z_g1;
                in >> self.constraint_system;
                return in;
            });
}

void declare_r1cs_ppzkadsnark_verification_key(py::module &m)
{
    // A verification key for the R1CS ppzkADSNARK.

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_verification_key<ppT>>(m, "r1cs_ppzkadsnark_verification_key")
        .def(py::init<>())
        .def("G1_size", &r1cs_ppzkadsnark_verification_key<ppT>::G1_size)
        .def("G2_size", &r1cs_ppzkadsnark_verification_key<ppT>::G2_size)
        .def("size_in_bits", &r1cs_ppzkadsnark_verification_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_ppzkadsnark_verification_key<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_ppzkadsnark_verification_key<ppT> const &self, r1cs_ppzkadsnark_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzkadsnark_verification_key<ppT> const &self) {
        std::ostringstream os;
        os << self.alphaA_g2 << OUTPUT_NEWLINE;
        os << self.alphaB_g1 << OUTPUT_NEWLINE;
        os << self.alphaC_g2 << OUTPUT_NEWLINE;
        os << self.gamma_g2 << OUTPUT_NEWLINE;
        os << self.gamma_beta_g1 << OUTPUT_NEWLINE;
        os << self.gamma_beta_g2 << OUTPUT_NEWLINE;
        os << self.rC_Z_g2 << OUTPUT_NEWLINE;
        os << self.A0 << OUTPUT_NEWLINE;
        os << self.Ain << OUTPUT_NEWLINE;
        return os;
            })
        .def("__istr__", [](r1cs_ppzkadsnark_verification_key<ppT> &self) {
                std::istringstream in;
                in >> self.alphaA_g2;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.alphaB_g1;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.alphaC_g2;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.gamma_g2;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.gamma_beta_g1;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.gamma_beta_g2;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.rC_Z_g2;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.A0;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.Ain;
                libff::consume_OUTPUT_NEWLINE(in);
                return in;
            });
}

void declare_r1cs_ppzkadsnark_processed_verification_key(py::module &m)
{
    // A processed verification key for the R1CS ppzkADSNARK.

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_processed_verification_key<ppT>>(m, "r1cs_ppzkadsnark_processed_verification_key")
        .def(py::init<>())
        .def(
            "__eq__", [](r1cs_ppzkadsnark_processed_verification_key<ppT> const &self, r1cs_ppzkadsnark_processed_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzkadsnark_processed_verification_key<ppT> const &self) {
        std::ostringstream os;
        os << self.pp_G2_one_precomp << OUTPUT_NEWLINE;
        os << self.vk_alphaA_g2_precomp << OUTPUT_NEWLINE;
        os << self.vk_alphaB_g1_precomp << OUTPUT_NEWLINE;
        os << self.vk_alphaC_g2_precomp << OUTPUT_NEWLINE;
        os << self.vk_rC_Z_g2_precomp << OUTPUT_NEWLINE;
        os << self.vk_gamma_g2_precomp << OUTPUT_NEWLINE;
        os << self.vk_gamma_beta_g1_precomp << OUTPUT_NEWLINE;
        os << self.vk_gamma_beta_g2_precomp << OUTPUT_NEWLINE;
        os << self.vk_rC_i_g2_precomp << OUTPUT_NEWLINE;
        os << self.A0 << OUTPUT_NEWLINE;
        os << self.Ain << OUTPUT_NEWLINE;
        os << self.proof_g_vki_precomp  << OUTPUT_NEWLINE;
        return os;
            })
        .def("__istr__", [](r1cs_ppzkadsnark_processed_verification_key<ppT> &self) {
                std::istringstream in;
                in >> self.pp_G2_one_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_alphaA_g2_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_alphaB_g1_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_alphaC_g2_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_rC_Z_g2_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_gamma_g2_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_gamma_beta_g1_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_gamma_beta_g2_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.vk_rC_i_g2_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.A0;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.Ain;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.proof_g_vki_precomp;
                libff::consume_OUTPUT_NEWLINE(in);
                return in;
            });
}

void declare_r1cs_ppzkadsnark_keypair(py::module &m)
{
    // A key pair for the R1CS ppzkADSNARK, which consists of a proving key and a verification key.

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_keypair<ppT>>(m, "r1cs_ppzkadsnark_keypair")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzkadsnark_keypair<ppT> &>());
}

void declare_r1cs_ppzkadsnark_proof(py::module &m)
{
    // A proof for the R1CS ppzkADSNARK.

    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<r1cs_ppzkadsnark_proof<ppT>>(m, "r1cs_ppzkadsnark_proof")
        .def(py::init<>())
        .def("G1_size", &r1cs_ppzkadsnark_proof<ppT>::G1_size)
        .def("G2_size", &r1cs_ppzkadsnark_proof<ppT>::G2_size)
        .def("size_in_bits", &r1cs_ppzkadsnark_proof<ppT>::size_in_bits)
        .def("print_size", &r1cs_ppzkadsnark_proof<ppT>::print_size)
        .def("is_well_formed", &r1cs_ppzkadsnark_proof<ppT>::is_well_formed)
        .def(
            "__eq__", [](r1cs_ppzkadsnark_proof<ppT> const &self, r1cs_ppzkadsnark_proof<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzkadsnark_proof<ppT> const &self) {
        std::ostringstream os;
        os << self.g_A << OUTPUT_NEWLINE;
        os << self.g_B << OUTPUT_NEWLINE;
        os << self.g_C << OUTPUT_NEWLINE;
        os << self.g_H << OUTPUT_NEWLINE;
        os << self.g_K << OUTPUT_NEWLINE;
        os << self.g_Aau << OUTPUT_NEWLINE;
        os << self.muA << OUTPUT_NEWLINE;
        return os;
            })
        .def("__istr__", [](r1cs_ppzkadsnark_proof<ppT> &self) {
                std::istringstream in;
                in >> self.g_A;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.g_B;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.g_C;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.g_H;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.g_K;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.g_Aau;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.muA;
                libff::consume_OUTPUT_NEWLINE(in);
                return in;
            });
}

void init_zk_proof_systems_ppzkadsnark_r1cs_ppzkadsnark_r1cs_ppzkadsnark(py::module &m)
{
    declare_r1cs_ppzkadsnark_pub_auth_prms(m);
    declare_r1cs_ppzkadsnark_sec_auth_key(m);
    declare_r1cs_ppzkadsnark_pub_auth_key(m);
    declare_r1cs_ppzkadsnark_auth_keys(m);
    declare_r1cs_ppzkadsnark_auth_data(m);
    declare_r1cs_ppzkadsnark_proving_key(m);
    declare_r1cs_ppzkadsnark_verification_key(m);
    declare_r1cs_ppzkadsnark_processed_verification_key(m);
    declare_r1cs_ppzkadsnark_keypair(m);
    declare_r1cs_ppzkadsnark_proof(m);
}