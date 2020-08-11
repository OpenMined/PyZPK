#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/r1cs_se_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_se_ppzksnark/r1cs_se_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a SEppzkSNARK for R1CS.
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

// SEppzkSNARK = "Simulation-Extractable PreProcessing Zero-Knowledge Succinct
//      Non-interactive ARgument of Knowledge"

void declare_r1cs_se_ppzksnark_proving_key(py::module &m)
{
    // A proving key for the R1CS SEppzkSNARK.
    using ppT = default_r1cs_se_ppzksnark_pp;

    py::class_<r1cs_se_ppzksnark_proving_key<ppT>>(m, "r1cs_se_ppzksnark_proving_key")
        .def(py::init<>())
        .def(py::init<const r1cs_se_ppzksnark_proving_key<ppT> &>())
        .def("G1_size", &r1cs_se_ppzksnark_proving_key<ppT>::G1_size)
        .def("G2_size", &r1cs_se_ppzksnark_proving_key<ppT>::G2_size)
        .def("size_in_bits", &r1cs_se_ppzksnark_proving_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_se_ppzksnark_proving_key<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_se_ppzksnark_proving_key<ppT> const &self, r1cs_se_ppzksnark_proving_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_se_ppzksnark_proving_key<ppT> const &self) {
        std::ostringstream os;
        os << self.A_query;
        os << self.B_query;
        os << self.C_query_1;
        os << self.C_query_2;
        os << self.G_gamma_Z;
        os << self.H_gamma_Z;
        os << self.G_ab_gamma_Z;
        os << self.G_gamma2_Z2;
        os << self.G_gamma2_Z_t;
        os << self.constraint_system;
        return os;
            })
        .def("__istr__", [](r1cs_se_ppzksnark_proving_key<ppT> &self) {
                std::istringstream in;
                in >> self.A_query;
                in >> self.B_query;
                in >> self.C_query_1;
                in >> self.C_query_2;
                in >> self.G_gamma_Z;
                in >> self.H_gamma_Z;
                in >> self.G_ab_gamma_Z;
                in >> self.G_gamma2_Z2;
                in >> self.G_gamma2_Z_t;
                in >> self.constraint_system;
                return in;
            });
}

void declare_r1cs_se_ppzksnark_verification_key(py::module &m)
{
    // A verification key for the R1CS SEppzkSNARK.
    using ppT = default_r1cs_se_ppzksnark_pp;

    py::class_<r1cs_se_ppzksnark_verification_key<ppT>>(m, "r1cs_se_ppzksnark_verification_key")
        .def(py::init<>())
        .def(py::init<const libff::G2<ppT> &,
            const libff::G1<ppT> &,
            const libff::G2<ppT> &,
            const libff::G1<ppT> &,
            const libff::G2<ppT> &,
            libff::G1_vector<ppT> &&>())
        .def("G1_size", &r1cs_se_ppzksnark_verification_key<ppT>::G1_size)
        .def("G2_size", &r1cs_se_ppzksnark_verification_key<ppT>::G2_size)
        .def("size_in_bits", &r1cs_se_ppzksnark_verification_key<ppT>::size_in_bits)
        .def("print_size", &r1cs_se_ppzksnark_verification_key<ppT>::print_size)
        .def(
            "__eq__", [](r1cs_se_ppzksnark_verification_key<ppT> const &self, r1cs_se_ppzksnark_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_se_ppzksnark_verification_key<ppT> const &self) {
        std::ostringstream os;
        os << self.H << OUTPUT_NEWLINE;
        os << self.G_alpha << OUTPUT_NEWLINE;
        os << self.H_beta << OUTPUT_NEWLINE;
        os << self.G_gamma << OUTPUT_NEWLINE;
        os << self.H_gamma << OUTPUT_NEWLINE;
        os << self.query << OUTPUT_NEWLINE;
        return os;
            })
        .def("__istr__", [](r1cs_se_ppzksnark_verification_key<ppT> &self) {
                std::istringstream in;
                in >> self.H;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.G_alpha;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.H_beta;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.G_gamma;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.H_gamma;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.query;
                libff::consume_OUTPUT_NEWLINE(in);
                return in;
            });
}

void declare_r1cs_se_ppzksnark_processed_verification_key(py::module &m)
{
    // A processed verification key for the R1CS SEppzkSNARK.
    using ppT = default_r1cs_se_ppzksnark_pp;

    py::class_<r1cs_se_ppzksnark_processed_verification_key<ppT>>(m, "r1cs_se_ppzksnark_processed_verification_key")
        .def(py::init<>())
        .def(
            "__eq__", [](r1cs_se_ppzksnark_processed_verification_key<ppT> const &self, r1cs_se_ppzksnark_processed_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_se_ppzksnark_processed_verification_key<ppT> const &self) {
        std::ostringstream os;
        os << self.G_alpha << OUTPUT_NEWLINE;
        os << self.H_beta << OUTPUT_NEWLINE;
        os << self.G_alpha_H_beta_ml << OUTPUT_NEWLINE;
        os << self.G_gamma_pc << OUTPUT_NEWLINE;
        os << self.H_gamma_pc << OUTPUT_NEWLINE;
        os << self.H_pc << OUTPUT_NEWLINE;
        os << self.query << OUTPUT_NEWLINE;
        return os;
            })
        .def("__istr__", [](r1cs_se_ppzksnark_processed_verification_key<ppT> &self) {
                std::istringstream in;
                in >> self.G_alpha;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.H_beta;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.G_alpha_H_beta_ml;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.G_gamma_pc;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.H_gamma_pc;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.H_pc;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.query;
                libff::consume_OUTPUT_NEWLINE(in);
                return in;
            });
}

void declare_r1cs_se_ppzksnark_keypair(py::module &m)
{
    // A key pair for the R1CS SEppzkSNARK, which consists of a proving key and a verification key.
    using ppT = default_r1cs_se_ppzksnark_pp;

    py::class_<r1cs_se_ppzksnark_keypair<ppT>>(m, "r1cs_se_ppzksnark_keypair")
        .def(py::init<>())
        .def(py::init<const r1cs_se_ppzksnark_keypair<ppT> &>());
}

void declare_r1cs_se_ppzksnark_proof(py::module &m)
{
    // A verification key for the R1CS SEppzkSNARK.
    using ppT = default_r1cs_se_ppzksnark_pp;

    py::class_<r1cs_se_ppzksnark_proof<ppT>>(m, "r1cs_se_ppzksnark_proof")
        .def(py::init<>())
        .def("G1_size", &r1cs_se_ppzksnark_proof<ppT>::G1_size)
        .def("G2_size", &r1cs_se_ppzksnark_proof<ppT>::G2_size)
        .def("size_in_bits", &r1cs_se_ppzksnark_proof<ppT>::size_in_bits)
        .def("print_size", &r1cs_se_ppzksnark_proof<ppT>::print_size)
        .def("is_well_formed", &r1cs_se_ppzksnark_proof<ppT>::is_well_formed)
        .def(
            "__eq__", [](r1cs_se_ppzksnark_proof<ppT> const &self, r1cs_se_ppzksnark_proof<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_se_ppzksnark_proof<ppT> const &self) {
        std::ostringstream os;
        os << self.A << OUTPUT_NEWLINE;
        os << self.B << OUTPUT_NEWLINE;
        os << self.C << OUTPUT_NEWLINE;
        return os;
            })
        .def("__istr__", [](r1cs_se_ppzksnark_proof<ppT> &self) {
                std::istringstream in;
                in >> self.A;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.B;
                libff::consume_OUTPUT_NEWLINE(in);
                in >> self.C;
                libff::consume_OUTPUT_NEWLINE(in);
                return in;
            });
}

void declare_r1cs_se_Main_Algorithms(py::module &m)
{
    using ppT = default_r1cs_se_ppzksnark_pp;

    // A generator algorithm for the R1CS SEppzkSNARK.
    m.def("r1cs_se_ppzksnark_generator", &r1cs_se_ppzksnark_generator<ppT>);

    // A prover algorithm for the R1CS SEppzkSNARK.
    m.def("r1cs_se_ppzksnark_prover", &r1cs_se_ppzksnark_prover<ppT>);

    // A verifier algorithm for the R1CS SEppzkSNARK that:
    //(1) accepts a non-processed verification key, and
    //(2) has weak input consistency.
    m.def("r1cs_se_ppzksnark_verifier_weak_IC", &r1cs_se_ppzksnark_verifier_weak_IC<ppT>);

    // A verifier algorithm for the R1CS SEppzkSNARK that:
    //(1) accepts a non-processed verification key, and
    //(2) has strong input consistency.
    m.def("r1cs_se_ppzksnark_verifier_strong_IC", &r1cs_se_ppzksnark_verifier_strong_IC<ppT>);

    // Convert a (non-processed) verification key into a processed verification key.
    m.def("r1cs_se_ppzksnark_online_verifier_weak_IC", &r1cs_se_ppzksnark_online_verifier_weak_IC<ppT>);

    // A verifier algorithm for the R1CS ppzkSNARK that:
    //(1) accepts a processed verification key, and
    //(2) has weak input consistency.
    m.def("r1cs_se_ppzksnark_verifier_process_vk", &r1cs_se_ppzksnark_verifier_process_vk<ppT>);

    // A verifier algorithm for the R1CS ppzkSNARK that:
    //(1) accepts a processed verification key, and
    //(2) has strong input consistency.
    m.def("r1cs_se_ppzksnark_online_verifier_strong_IC", &r1cs_se_ppzksnark_online_verifier_strong_IC<ppT>);
}

void init_zk_proof_systems_ppzksnark_r1cs_se_ppzksnark_r1cs_se_ppzksnark(py::module &m)
{
    declare_r1cs_se_ppzksnark_proving_key(m);
    declare_r1cs_se_ppzksnark_verification_key(m);
    declare_r1cs_se_ppzksnark_processed_verification_key(m);
    declare_r1cs_se_ppzksnark_keypair(m);
    declare_r1cs_se_ppzksnark_proof(m);
    declare_r1cs_se_Main_Algorithms(m);
}