#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for a ppzkSNARK for R1CS.
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

void declare_r1cs_ppzksnark_proving_key(py::module &m)
{
    // A proving key for the R1CS ppzkSNARK.
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_proving_key<ppT>>(m, "r1cs_ppzksnark_proving_key")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzksnark_proving_key<ppT> &>())
        .def_readwrite("A_query", &r1cs_ppzksnark_proving_key<ppT>::A_query)
        .def_readwrite("B_query", &r1cs_ppzksnark_proving_key<ppT>::B_query)
        .def_readwrite("C_query", &r1cs_ppzksnark_proving_key<ppT>::C_query)
        .def_readwrite("H_query", &r1cs_ppzksnark_proving_key<ppT>::H_query)
        .def_readwrite("K_query", &r1cs_ppzksnark_proving_key<ppT>::K_query)
        .def_readwrite("constraint_system", &r1cs_ppzksnark_proving_key<ppT>::constraint_system)
        .def("G1_size", &r1cs_ppzksnark_proving_key<ppT>::G1_size)
        .def("G2_size", &r1cs_ppzksnark_proving_key<ppT>::G2_size)
        .def("G1_sparse_size", &r1cs_ppzksnark_proving_key<ppT>::G1_sparse_size)
        .def("G2_sparse_size", &r1cs_ppzksnark_proving_key<ppT>::G2_sparse_size)
        .def("size_in_bits", &r1cs_ppzksnark_proving_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_ppzksnark_proving_key<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_ppzksnark_proving_key<ppT> const &self, r1cs_ppzksnark_proving_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzksnark_proving_key<ppT> const &self) {
            std::ostringstream os;
            os << self.A_query;
            os << self.B_query;
            os << self.C_query;
            os << self.H_query;
            os << self.K_query;
            os << self.constraint_system;
            return os;
        })
        .def("__istr__", [](r1cs_ppzksnark_proving_key<ppT> &self) {
            std::istringstream in;
            in >> self.A_query;
            in >> self.B_query;
            in >> self.C_query;
            in >> self.H_query;
            in >> self.K_query;
            in >> self.constraint_system;
            return in;
        });
}

void declare_r1cs_ppzksnark_verification_key(py::module &m)
{
    // A verification key for the R1CS ppzkSNARK.
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_verification_key<ppT>>(m, "r1cs_ppzksnark_verification_key")
        .def(py::init<>())
        .def(py::init<const libff::G2<ppT> &,
                      const libff::G1<ppT> &,
                      const libff::G2<ppT> &,
                      const libff::G2<ppT> &,
                      const libff::G1<ppT> &,
                      const libff::G2<ppT> &,
                      const libff::G2<ppT> &,
                      const accumulation_vector<libff::G1<ppT>> &>())
        .def_readwrite("alphaA_g2", &r1cs_ppzksnark_verification_key<ppT>::alphaA_g2)
        .def_readwrite("alphaB_g1", &r1cs_ppzksnark_verification_key<ppT>::alphaB_g1)
        .def_readwrite("alphaC_g2", &r1cs_ppzksnark_verification_key<ppT>::alphaC_g2)
        .def_readwrite("gamma_g2", &r1cs_ppzksnark_verification_key<ppT>::gamma_g2)
        .def_readwrite("gamma_beta_g1", &r1cs_ppzksnark_verification_key<ppT>::gamma_beta_g1)
        .def_readwrite("gamma_beta_g2", &r1cs_ppzksnark_verification_key<ppT>::gamma_beta_g2)
        .def_readwrite("rC_Z_g2", &r1cs_ppzksnark_verification_key<ppT>::rC_Z_g2)
        .def("G1_size", &r1cs_ppzksnark_verification_key<ppT>::G1_size)
        .def("G2_size", &r1cs_ppzksnark_verification_key<ppT>::G2_size)
        .def("size_in_bits", &r1cs_ppzksnark_verification_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_ppzksnark_verification_key<ppT>::print_size)
        .def_static("dummy_verification_key", &r1cs_ppzksnark_verification_key<ppT>::dummy_verification_key)
        .def(
            "__eq__", [](r1cs_ppzksnark_verification_key<ppT> const &self, r1cs_ppzksnark_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzksnark_verification_key<ppT> const &self) {
            std::ostringstream os;
            os << self.alphaA_g2 << OUTPUT_NEWLINE;
            os << self.alphaB_g1 << OUTPUT_NEWLINE;
            os << self.alphaC_g2 << OUTPUT_NEWLINE;
            os << self.gamma_g2 << OUTPUT_NEWLINE;
            os << self.gamma_beta_g1 << OUTPUT_NEWLINE;
            os << self.gamma_beta_g2 << OUTPUT_NEWLINE;
            os << self.rC_Z_g2 << OUTPUT_NEWLINE;
            os << self.encoded_IC_query << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](r1cs_ppzksnark_verification_key<ppT> &self) {
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
            in >> self.encoded_IC_query;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_r1cs_ppzksnark_processed_verification_key(py::module &m)
{
    // A verification key for the R1CS ppzkSNARK.
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_processed_verification_key<ppT>>(m, "r1cs_ppzksnark_processed_verification_key")
        .def(py::init<>())
        .def_readwrite("pp_G2_one_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::pp_G2_one_precomp)
        .def_readwrite("vk_alphaA_g2_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::vk_alphaA_g2_precomp)
        .def_readwrite("vk_alphaB_g1_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::vk_alphaB_g1_precomp)
        .def_readwrite("vk_alphaC_g2_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::vk_alphaC_g2_precomp)
        .def_readwrite("vk_rC_Z_g2_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::vk_rC_Z_g2_precomp)
        .def_readwrite("vk_gamma_g2_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::vk_gamma_g2_precomp)
        .def_readwrite("vk_gamma_beta_g1_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::vk_gamma_beta_g1_precomp)
        .def_readwrite("vk_gamma_beta_g2_precomp", &r1cs_ppzksnark_processed_verification_key<ppT>::vk_gamma_beta_g2_precomp)
        .def_readwrite("encoded_IC_query", &r1cs_ppzksnark_processed_verification_key<ppT>::encoded_IC_query)
        .def(
            "__eq__", [](r1cs_ppzksnark_processed_verification_key<ppT> const &self, r1cs_ppzksnark_processed_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzksnark_processed_verification_key<ppT> const &self) {
            std::ostringstream os;
            os << self.pp_G2_one_precomp << OUTPUT_NEWLINE;
            os << self.vk_alphaA_g2_precomp << OUTPUT_NEWLINE;
            os << self.vk_alphaB_g1_precomp << OUTPUT_NEWLINE;
            os << self.vk_alphaC_g2_precomp << OUTPUT_NEWLINE;
            os << self.vk_rC_Z_g2_precomp << OUTPUT_NEWLINE;
            os << self.vk_gamma_g2_precomp << OUTPUT_NEWLINE;
            os << self.vk_gamma_beta_g1_precomp << OUTPUT_NEWLINE;
            os << self.vk_gamma_beta_g2_precomp << OUTPUT_NEWLINE;
            os << self.encoded_IC_query << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](r1cs_ppzksnark_processed_verification_key<ppT> &self) {
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
            in >> self.encoded_IC_query;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}

void declare_r1cs_ppzksnark_keypair(py::module &m)
{
    // A key pair for the R1CS ppzkSNARK, which consists of a proving key and a verification key.
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_keypair<ppT>>(m, "r1cs_ppzksnark_keypair")
        .def(py::init<>())
        .def(py::init<const r1cs_ppzksnark_keypair<ppT> &>())
        .def_readwrite("pk", &r1cs_ppzksnark_keypair<ppT>::pk)
        .def_readwrite("vk", &r1cs_ppzksnark_keypair<ppT>::vk);
}

void declare_r1cs_ppzksnark_proof(py::module &m)
{
    // A verification key for the R1CS ppzkSNARK.
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;

    py::class_<r1cs_ppzksnark_proof<ppT>>(m, "r1cs_ppzksnark_proof")
        .def(py::init<>())
        .def_readwrite("g_A", &r1cs_ppzksnark_proof<ppT>::g_A)
        .def_readwrite("g_B", &r1cs_ppzksnark_proof<ppT>::g_B)
        .def_readwrite("g_C", &r1cs_ppzksnark_proof<ppT>::g_C)
        .def_readwrite("g_H", &r1cs_ppzksnark_proof<ppT>::g_H)
        .def_readwrite("g_K", &r1cs_ppzksnark_proof<ppT>::g_K)
        .def("G1_size", &r1cs_ppzksnark_proof<ppT>::G1_size)
        .def("G2_size", &r1cs_ppzksnark_proof<ppT>::G2_size)
        .def("size_in_bits", &r1cs_ppzksnark_proof<ppT>::size_in_bits)
        .def("print_size", &r1cs_ppzksnark_proof<ppT>::print_size)
        .def("is_well_formed", &r1cs_ppzksnark_proof<ppT>::is_well_formed)
        .def(
            "__eq__", [](r1cs_ppzksnark_proof<ppT> const &self, r1cs_ppzksnark_proof<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_ppzksnark_proof<ppT> const &self) {
            std::ostringstream os;
            os << self.g_A << OUTPUT_NEWLINE;
            os << self.g_B << OUTPUT_NEWLINE;
            os << self.g_C << OUTPUT_NEWLINE;
            os << self.g_H << OUTPUT_NEWLINE;
            os << self.g_K << OUTPUT_NEWLINE;
            return os;
        })
        .def("__istr__", [](r1cs_ppzksnark_proof<ppT> &self) {
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
            return in;
        });
}

void declare_Main_algorithms(py::module &m)
{
    using ppT = mnt6_pp;

    m.def("r1cs_ppzksnark_generator", &r1cs_ppzksnark_generator<ppT>, "A generator algorithm for the R1CS ppzkSNARK Given a R1CS constraint system CS, this algorithm produces proving and verification keys for C");
    m.def("r1cs_ppzksnark_prover", &r1cs_ppzksnark_prover<ppT>, "A prover algorithm for the R1CS ppzkSNARK.");
    m.def("r1cs_ppzksnark_verifier_weak_IC", &r1cs_ppzksnark_verifier_weak_IC<ppT>, "A verifier algorithm for the R1CS ppzkSNARK");
    m.def("r1cs_ppzksnark_verifier_strong_IC", &r1cs_ppzksnark_verifier_strong_IC<ppT>, "A verifier algorithm for the R1CS ppzkSNARK");
    m.def("r1cs_ppzksnark_verifier_process_vk", &r1cs_ppzksnark_verifier_process_vk<ppT>, "Convert a (non-processed) verification key into a processed verification key.");
    m.def("r1cs_ppzksnark_online_verifier_weak_IC", &r1cs_ppzksnark_online_verifier_weak_IC<ppT>, "A verifier algorithm for the R1CS ppzkSNARK");
    m.def("r1cs_ppzksnark_online_verifier_strong_IC", &r1cs_ppzksnark_online_verifier_strong_IC<ppT>, "A verifier algorithm for the R1CS ppzkSNARK");
    m.def("r1cs_ppzksnark_affine_verifier_weak_IC", &r1cs_ppzksnark_affine_verifier_weak_IC<ppT>, "A verifier algorithm for the R1CS ppzkSNARK");
}

void init_zk_proof_systems_ppzksnark_r1cs_ppzksnark_r1cs_ppzksnark(py::module &m)
{
    declare_r1cs_ppzksnark_proving_key(m);
    declare_r1cs_ppzksnark_verification_key(m);
    declare_r1cs_ppzksnark_processed_verification_key(m);
    declare_r1cs_ppzksnark_keypair(m);
    declare_r1cs_ppzksnark_proof(m);
    declare_Main_algorithms(m);
}