#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/common/default_types/r1cs_ppzkpcd_pp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_mp_ppzkpcd/r1cs_mp_ppzkpcd.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for a multi-predicate ppzkPCD for R1CS.

void declare_r1cs_mp_ppzkpcd_proving_key(py::module &m)
{
    // A proving key for the R1CS (multi-predicate) ppzkPCD.
    using PCD_ppT = default_r1cs_ppzkpcd_pp;
    typedef typename PCD_ppT::curve_A_pp A_pp;
    typedef typename PCD_ppT::curve_B_pp B_pp;

    py::class_<r1cs_mp_ppzkpcd_proving_key<PCD_ppT>>(m, "r1cs_mp_ppzkpcd_proving_key")
        .def(py::init<>())
        .def(py::init<const r1cs_mp_ppzkpcd_proving_key<PCD_ppT> &>())
        .def(py::init<const std::vector<r1cs_mp_ppzkpcd_compliance_predicate<PCD_ppT>> &,
                      const std::vector<r1cs_ppzksnark_proving_key<A_pp>> &,
                      const std::vector<r1cs_ppzksnark_proving_key<B_pp>> &,
                      const std::vector<r1cs_ppzksnark_verification_key<A_pp>> &,
                      const std::vector<r1cs_ppzksnark_verification_key<B_pp>> &,
                      const set_commitment &,
                      const std::vector<set_membership_proof> &,
                      const std::map<size_t, size_t> &>())
        .def_readwrite("compliance_predicates", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::compliance_predicates)
        .def_readwrite("compliance_step_r1cs_pks", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::compliance_step_r1cs_pks)
        .def_readwrite("translation_step_r1cs_pks", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::translation_step_r1cs_pks)
        .def_readwrite("compliance_step_r1cs_vks", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::compliance_step_r1cs_vks)
        .def_readwrite("translation_step_r1cs_vks", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::translation_step_r1cs_vks)
        .def_readwrite("commitment_to_translation_step_r1cs_vks", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::commitment_to_translation_step_r1cs_vks)
        .def_readwrite("compliance_step_r1cs_vk_membership_proofs", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::compliance_step_r1cs_vk_membership_proofs)
        .def_readwrite("compliance_predicate_name_to_idx", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::compliance_predicate_name_to_idx)
        .def("is_well_formed", &r1cs_mp_ppzkpcd_proving_key<PCD_ppT>::is_well_formed)
        .def("__ostr__", [](r1cs_mp_ppzkpcd_proving_key<PCD_ppT> const &self) {
            std::ostringstream os;
            os << self.compliance_predicates;
            os << self.compliance_step_r1cs_pks;
            os << self.translation_step_r1cs_pks;
            os << self.compliance_step_r1cs_vks;
            os << self.translation_step_r1cs_vks;
            output_bool_vector(os, self.commitment_to_translation_step_r1cs_vks);
            os << self.compliance_step_r1cs_vk_membership_proofs;
            os << self.compliance_predicate_name_to_idx;
            return os;
        })
        .def("__istr__", [](r1cs_mp_ppzkpcd_proving_key<PCD_ppT> &self) {
            std::istringstream in;
            in >> self.compliance_predicates;
            in >> self.compliance_step_r1cs_pks;
            in >> self.translation_step_r1cs_pks;
            in >> self.compliance_step_r1cs_vks;
            in >> self.translation_step_r1cs_vks;
            input_bool_vector(in, self.commitment_to_translation_step_r1cs_vks);
            in >> self.compliance_step_r1cs_vk_membership_proofs;
            in >> self.compliance_predicate_name_to_idx;
            return in;
        });
}

void declare_r1cs_mp_ppzkpcd_verification_key(py::module &m)
{
    //  A verification key for the R1CS (multi-predicate) ppzkPCD.
    using PCD_ppT = default_r1cs_ppzkpcd_pp;
    typedef typename PCD_ppT::curve_A_pp A_pp;
    typedef typename PCD_ppT::curve_B_pp B_pp;

    py::class_<r1cs_mp_ppzkpcd_verification_key<PCD_ppT>>(m, "r1cs_mp_ppzkpcd_verification_key")
        .def(py::init<>())
        .def(py::init<const r1cs_mp_ppzkpcd_verification_key<PCD_ppT> &>())
        .def(py::init<const std::vector<r1cs_ppzksnark_verification_key<A_pp>> &,
                      const std::vector<r1cs_ppzksnark_verification_key<B_pp>> &,
                      const set_commitment &>())
        .def_readwrite("compliance_step_r1cs_vks", &r1cs_mp_ppzkpcd_verification_key<PCD_ppT>::compliance_step_r1cs_vks)
        .def_readwrite("translation_step_r1cs_vks", &r1cs_mp_ppzkpcd_verification_key<PCD_ppT>::translation_step_r1cs_vks)
        .def_readwrite("commitment_to_translation_step_r1cs_vks", &r1cs_mp_ppzkpcd_verification_key<PCD_ppT>::commitment_to_translation_step_r1cs_vks)
        .def("size_in_bits", &r1cs_mp_ppzkpcd_verification_key<PCD_ppT>::size_in_bits)
        .def(
            "__eq__", [](r1cs_mp_ppzkpcd_verification_key<PCD_ppT> const &self, r1cs_mp_ppzkpcd_verification_key<PCD_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_mp_ppzkpcd_verification_key<PCD_ppT> const &self) {
            std::ostringstream os;
            os << self.compliance_step_r1cs_vks;
            os << self.translation_step_r1cs_vks;
            libff::output_bool_vector(os, self.commitment_to_translation_step_r1cs_vks);
            return os;
        })
        .def("__istr__", [](r1cs_mp_ppzkpcd_verification_key<PCD_ppT> &self) {
            std::istringstream in;
            in >> self.compliance_step_r1cs_vks;
            in >> self.translation_step_r1cs_vks;
            libff::input_bool_vector(in, self.commitment_to_translation_step_r1cs_vks);
            return in;
        });
}

void declare_r1cs_mp_ppzkpcd_processed_verification_key(py::module &m)
{
    // A processed verification key for the R1CS (multi-predicate) ppzkPCD.
    // Compared to a (non-processed) verification key, a processed verification key
    // contains a small constant amount of additional pre-computed information that
    // enables a faster verification time.

    using PCD_ppT = default_r1cs_ppzkpcd_pp;
    typedef typename PCD_ppT::curve_A_pp A_pp;
    typedef typename PCD_ppT::curve_B_pp B_pp;

    py::class_<r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT>>(m, "r1cs_mp_ppzkpcd_processed_verification_key")
        .def(py::init<>())
        .def(py::init<const r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT> &>())
        .def(py::init<std::vector<r1cs_ppzksnark_processed_verification_key<A_pp>> &&,
                      std::vector<r1cs_ppzksnark_processed_verification_key<B_pp>> &&,
                      const set_commitment &>())
        .def_readwrite("compliance_step_r1cs_pvks", &r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT>::compliance_step_r1cs_pvks)
        .def_readwrite("translation_step_r1cs_pvks", &r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT>::translation_step_r1cs_pvks)
        .def_readwrite("commitment_to_translation_step_r1cs_vks", &r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT>::commitment_to_translation_step_r1cs_vks)
        .def(
            "__eq__", [](r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT> const &self, r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT> const &self) {
            std::ostringstream os;
            os << self.compliance_step_r1cs_pvks;
            os << self.translation_step_r1cs_pvks;
            libff::output_bool_vector(os, self.commitment_to_translation_step_r1cs_vks);
            return os;
        })
        .def("__istr__", [](r1cs_mp_ppzkpcd_processed_verification_key<PCD_ppT> &self) {
            std::istringstream in;
            in >> self.compliance_step_r1cs_pvks;
            in >> self.translation_step_r1cs_pvks;
            libff::input_bool_vector(in, self.commitment_to_translation_step_r1cs_vks);
            return in;
        });
}

void declare_r1cs_mp_ppzkpcd_keypair(py::module &m)
{
    // A key pair for the R1CS (multi-predicate) ppzkPC, which consists of a proving key and a verification key.

    using PCD_ppT = default_r1cs_ppzkpcd_pp;

    py::class_<r1cs_mp_ppzkpcd_keypair<PCD_ppT>>(m, "r1cs_mp_ppzkpcd_keypair")
        .def(py::init<>())
        .def_readwrite("pk", &r1cs_mp_ppzkpcd_keypair<PCD_ppT>::pk)
        .def_readwrite("vk", &r1cs_mp_ppzkpcd_keypair<PCD_ppT>::vk);
}

void declare_r1cs_mp_ppzkpcd_proof(py::module &m)
{
    // A proof for the R1CS (multi-predicate) ppzkPCD.

    using PCD_ppT = default_r1cs_ppzkpcd_pp;

    py::class_<r1cs_mp_ppzkpcd_proof<PCD_ppT>>(m, "r1cs_mp_ppzkpcd_proof")
        .def(py::init<>())
        .def(py::init<const size_t,
                      const r1cs_ppzksnark_proof<typename PCD_ppT::curve_B_pp> &>())
        .def_readwrite("compliance_predicate_idx", &r1cs_mp_ppzkpcd_proof<PCD_ppT>::compliance_predicate_idx)
        .def_readwrite("r1cs_proof", &r1cs_mp_ppzkpcd_proof<PCD_ppT>::r1cs_proof)
        .def(
            "__eq__", [](r1cs_mp_ppzkpcd_proof<PCD_ppT> const &self, r1cs_mp_ppzkpcd_proof<PCD_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_mp_ppzkpcd_proof<PCD_ppT> const &self) {
            std::ostringstream os;
            os << self.compliance_predicate_idx << "\n";
            os << self.r1cs_proof;
            return os;
        })
        .def("__istr__", [](r1cs_mp_ppzkpcd_proof<PCD_ppT> &self) {
            std::istringstream in;
            in >> self.compliance_predicate_idx;
            libff::consume_newline(in);
            in >> self.r1cs_proof;
            return in;
        });
}

void declare_mp_Main_algorithms(py::module &m)
{
    // A proof for the R1CS (multi-predicate) ppzkPCD.

    using PCD_ppT = default_r1cs_ppzkpcd_pp;

    // A generator algorithm for the R1CS (multi-predicate) ppzkPCD. 
    // Given a vector of compliance predicates, this algorithm produces proving and verification keys for the vector.
    m.def("r1cs_mp_ppzkpcd_generator", &r1cs_mp_ppzkpcd_generator<PCD_ppT>);

    // A prover algorithm for the R1CS (multi-predicate) ppzkPCD.
    // Given a proving key, name of chosen compliance predicate, inputs for the
    // compliance predicate, and proofs for the predicate's input messages, this
    // algorithm produces a proof (of knowledge) that attests to the compliance of
    // the output message.
    m.def("r1cs_mp_ppzkpcd_prover", &r1cs_mp_ppzkpcd_prover<PCD_ppT>);

    // A verifier algorithm for the R1CS (multi-predicate) ppzkPCD that accepts a non-processed verification key.
    m.def("r1cs_mp_ppzkpcd_verifier", &r1cs_mp_ppzkpcd_verifier<PCD_ppT>);

    // Convert a (non-processed) verification key into a processed verification key.
    m.def("r1cs_mp_ppzkpcd_process_vk", &r1cs_mp_ppzkpcd_process_vk<PCD_ppT>);

    // A verifier algorithm for the R1CS (multi-predicate) ppzkPCD that accepts a processed verification key.
    m.def("r1cs_mp_ppzkpcd_online_verifier", &r1cs_mp_ppzkpcd_online_verifier<PCD_ppT>);
}

void init_zk_proof_systems_pcd_r1cs_pcd_r1cs_mp_ppzkpcd_r1cs_mp_ppzkpcd(py::module &m)
{
    declare_r1cs_mp_ppzkpcd_proving_key(m);
    declare_r1cs_mp_ppzkpcd_verification_key(m);
    declare_r1cs_mp_ppzkpcd_processed_verification_key(m);
    declare_r1cs_mp_ppzkpcd_keypair(m);
    declare_r1cs_mp_ppzkpcd_proof(m);
    declare_mp_Main_algorithms(m);
}