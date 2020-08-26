#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/common/default_types/r1cs_ppzkpcd_pp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_sp_ppzkpcd/r1cs_sp_ppzkpcd.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for a *single-predicate* ppzkPCD for R1CS.

void declare_r1cs_sp_ppzkpcd_proving_key(py::module &m)
{
    // A proving key for the R1CS (single-predicate) ppzkPCD.
    using PCD_ppT = default_r1cs_ppzkpcd_pp;
    typedef typename PCD_ppT::curve_A_pp A_pp;
    typedef typename PCD_ppT::curve_B_pp B_pp;

    py::class_<r1cs_sp_ppzkpcd_proving_key<PCD_ppT>>(m, "r1cs_sp_ppzkpcd_proving_key")
        .def(py::init<>())
        .def(py::init<const r1cs_sp_ppzkpcd_proving_key<PCD_ppT> &>())
        .def("size_in_bits", &r1cs_sp_ppzkpcd_proving_key<PCD_ppT>::size_in_bits)
        .def(
            "__eq__", [](r1cs_sp_ppzkpcd_proving_key<PCD_ppT> const &self, r1cs_sp_ppzkpcd_proving_key<PCD_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_sp_ppzkpcd_proving_key<PCD_ppT> const &self) {
        std::ostringstream os;
        os << self.compliance_predicate;
        os << self.compliance_step_r1cs_pk;
        os << self.translation_step_r1cs_pk;
        os << self.compliance_step_r1cs_vk;
        os << self.translation_step_r1cs_vk;
        return os;
            })
        .def("__istr__", [](r1cs_sp_ppzkpcd_proving_key<PCD_ppT> &self) {
                std::istringstream in;
                in >> self.compliance_predicate;
                in >> self.compliance_step_r1cs_pk;
                in >> self.translation_step_r1cs_pk;
                in >> self.compliance_step_r1cs_vk;
                in >> self.translation_step_r1cs_vk;
                return in;
            });
}

void declare_r1cs_sp_ppzkpcd_verification_key(py::module &m)
{
    // A verification key for the R1CS (single-predicate) ppzkPCD.
    using PCD_ppT = default_r1cs_ppzkpcd_pp;
    typedef typename PCD_ppT::curve_A_pp A_pp;
    typedef typename PCD_ppT::curve_B_pp B_pp;

    py::class_<r1cs_sp_ppzkpcd_verification_key<PCD_ppT>>(m, "r1cs_sp_ppzkpcd_verification_key")
        .def(py::init<>())
        .def(py::init<const r1cs_sp_ppzkpcd_verification_key<PCD_ppT> &>())
        .def(py::init<const r1cs_ppzksnark_verification_key<A_pp> &,
            const r1cs_ppzksnark_verification_key<B_pp> &>())
        .def("size_in_bits", &r1cs_sp_ppzkpcd_verification_key<PCD_ppT>::size_in_bits)
        .def(
            "__eq__", [](r1cs_sp_ppzkpcd_verification_key<PCD_ppT> const &self, r1cs_sp_ppzkpcd_verification_key<PCD_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_sp_ppzkpcd_verification_key<PCD_ppT> const &self) {
        std::ostringstream os;
        os << self.compliance_step_r1cs_vk;
        os << self.translation_step_r1cs_vk;
        return os;
            })
        .def("__istr__", [](r1cs_sp_ppzkpcd_verification_key<PCD_ppT> &self) {
                std::istringstream in;
                in >> self.compliance_step_r1cs_vk;
                in >> self.translation_step_r1cs_vk;
                return in;
            });
}

void declare_r1cs_sp_ppzkpcd_processed_verification_key(py::module &m)
{
    // A processed verification key for the R1CS (single-predicate) ppzkPCD.
    using PCD_ppT = default_r1cs_ppzkpcd_pp;
    typedef typename PCD_ppT::curve_A_pp A_pp;
    typedef typename PCD_ppT::curve_B_pp B_pp;

    py::class_<r1cs_sp_ppzkpcd_processed_verification_key<PCD_ppT>>(m, "r1cs_sp_ppzkpcd_processed_verification_key")
        .def(py::init<>())
        .def(py::init<const r1cs_sp_ppzkpcd_processed_verification_key<PCD_ppT> &>())
        .def(
            "__eq__", [](r1cs_sp_ppzkpcd_processed_verification_key<PCD_ppT> const &self, r1cs_sp_ppzkpcd_processed_verification_key<PCD_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_sp_ppzkpcd_processed_verification_key<PCD_ppT> const &self) {
        std::ostringstream os;
        os << self.compliance_step_r1cs_pvk;
        os << self.translation_step_r1cs_pvk;
        libff::serialize_bit_vector(os, self.translation_step_r1cs_vk_bits);
        return os;
            })
        .def("__istr__", [](r1cs_sp_ppzkpcd_processed_verification_key<PCD_ppT> &self) {
                std::istringstream in;
                in >> self.compliance_step_r1cs_pvk;
                in >> self.translation_step_r1cs_pvk;
                libff::deserialize_bit_vector(in, self.translation_step_r1cs_vk_bits);
                return in;
            });
}

void declare_r1cs_sp_ppzkpcd_keypair(py::module &m)
{
    // A key pair for the R1CS (single-predicate) ppzkPC, which consists of a proving key and a verification key.
    using PCD_ppT = default_r1cs_ppzkpcd_pp;

    py::class_<r1cs_sp_ppzkpcd_keypair<PCD_ppT>>(m, "r1cs_sp_ppzkpcd_keypair")
        .def(py::init<>());
}

void declare_sp_Main_algorithms(py::module &m)
{
    using PCD_ppT = default_r1cs_ppzkpcd_pp;
    // A generator algorithm for the R1CS (single-predicate) ppzkPCD.
    // Given a compliance predicate, this algorithm produces proving and verification keys for the predicate.
    m.def("r1cs_sp_ppzkpcd_generator", &r1cs_sp_ppzkpcd_generator<PCD_ppT>, py::arg("compliance_predicate"));

    // A prover algorithm for the R1CS (single-predicate) ppzkPCD.
    // Given a proving key, inputs for the compliance predicate, and proofs for
    // the predicate's input messages, this algorithm produces a proof (of knowledge)
    // that attests to the compliance of the output message.
    m.def("r1cs_sp_ppzkpcd_prover", &r1cs_sp_ppzkpcd_prover<PCD_ppT>, py::arg("r1cs_sp_ppzkpcd_proving_key"), py::arg("primary_input"), py::arg("auxiliary_input"), py::arg("incoming_proofs"));

    // A verifier algorithm for the R1CS (single-predicate) ppzkPCD that accepts a non-processed verification key.
    m.def("r1cs_sp_ppzkpcd_verifier", &r1cs_sp_ppzkpcd_verifier<PCD_ppT>, py::arg("r1cs_sp_ppzkpcd_verification_key"), py::arg("primary_input"), py::arg("proof"));

    // Convert a (non-processed) verification key into a processed verification key.
    m.def("r1cs_sp_ppzkpcd_process_vk", &r1cs_sp_ppzkpcd_process_vk<PCD_ppT>, py::arg("r1cs_sp_ppzkpcd_verification_key"));

    // A verifier algorithm for the R1CS (single-predicate) ppzkPCD that accepts a processed verification key.
    m.def("r1cs_sp_ppzkpcd_online_verifier", &r1cs_sp_ppzkpcd_online_verifier<PCD_ppT>, py::arg("r1cs_sp_ppzkpcd_processed_verification_key"), py::arg("primary_input"), py::arg("proof"));

}

void init_zk_proof_systems_pcd_r1cs_pcd_r1cs_sp_ppzkpcd_r1cs_sp_ppzkpcd(py::module &m)
{
    declare_r1cs_sp_ppzkpcd_proving_key(m);
    declare_r1cs_sp_ppzkpcd_verification_key(m);
    declare_r1cs_sp_ppzkpcd_processed_verification_key(m);
    declare_r1cs_sp_ppzkpcd_keypair(m);
}