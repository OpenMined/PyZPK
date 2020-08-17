#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/ram_zksnark_pp.hpp>
#include <libsnark/zk_proof_systems/zksnark/ram_zksnark/ram_zksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for a zkSNARK for RAM.
//  This includes:
//  - the class for a proving key;
//  - the class for a verification key;
//  - the class for a key pair (proving key & verification key);
//  - the class for a proof;
//  - the generator algorithm;
//  - the prover algorithm;
//  - the verifier algorithm.

void declare_ram_zksnark_proving_key(py::module &m)
{
    // A proving key for the RAM zkSNARK.
    using ram_zksnark_ppT = default_ram_zksnark_pp;

    py::class_<ram_zksnark_proving_key<ram_zksnark_ppT>>(m, "ram_zksnark_proving_key")
        .def(py::init<>())
        .def(py::init<const ram_zksnark_proving_key<ram_zksnark_ppT> &>())
        .def(
            "__eq__", [](ram_zksnark_proving_key<ram_zksnark_ppT> const &self, ram_zksnark_proving_key<ram_zksnark_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](ram_zksnark_proving_key<ram_zksnark_ppT> const &pk) {
            std::ostringstream os;
            os << pk.ap;
            os << pk.pcd_pk;
            return os;
        })
        .def("__istr__", [](ram_zksnark_proving_key<ram_zksnark_ppT> &pk) {
            std::istringstream in;
            in >> pk.ap;
            in >> pk.pcd_pk;
            return in;
        });
}

void declare_ram_zksnark_verification_key(py::module &m)
{
    // A verification key for the RAM zkSNARK.
    using ram_zksnark_ppT = default_ram_zksnark_pp;

    py::class_<ram_zksnark_verification_key<ram_zksnark_ppT>>(m, "ram_zksnark_verification_key")
        .def(py::init<>())
        .def(py::init<const ram_zksnark_verification_key<ram_zksnark_ppT> &>())
        .def(
            "__eq__", [](ram_zksnark_verification_key<ram_zksnark_ppT> const &self, ram_zksnark_verification_key<ram_zksnark_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](ram_zksnark_verification_key<ram_zksnark_ppT> const &vk) {
            std::ostringstream os;
            os << vk.ap;
            os << vk.pcd_vk;
            return os;
        })
        .def("__istr__", [](ram_zksnark_verification_key<ram_zksnark_ppT> &vk) {
            std::istringstream in;
            in >> vk.ap;
            in >> vk.pcd_vk;
            return in;
        });
}

void declare_ram_zksnark_keypair(py::module &m)
{
    // A key pair for the RAM zkSNARK, which consists of a proving key and a verification key.
    using ram_zksnark_ppT = default_ram_zksnark_pp;

    py::class_<ram_zksnark_keypair<ram_zksnark_ppT>>(m, "ram_zksnark_keypair")
        .def(py::init<>());
}

void declare_ram_zksnark_proof(py::module &m)
{
    // A proof for the RAM zkSNARK.
    using ram_zksnark_ppT = default_ram_zksnark_pp;

    py::class_<ram_zksnark_proof<ram_zksnark_ppT>>(m, "ram_zksnark_proof")
        .def(py::init<>())
        .def(py::init<const ram_zksnark_proof<ram_zksnark_ppT> &>())
        .def("size_in_bits", &ram_zksnark_proof<ram_zksnark_ppT>::size_in_bits)
        .def(
            "__eq__", [](ram_zksnark_proof<ram_zksnark_ppT> const &self, ram_zksnark_proof<ram_zksnark_ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](ram_zksnark_proof<ram_zksnark_ppT> const &proof) {
            std::ostringstream os;

            os << proof.PCD_proof;
            return os;
        })
        .def("__istr__", [](ram_zksnark_proof<ram_zksnark_ppT> &proof) {
            std::istringstream in;
            in >> proof.PCD_proof;
            return in;
        });
}

void declare_RAM_zksnark_Main_Algorithms(py::module &m)
{
    using ram_zksnark_ppT = default_ram_zksnark_pp;

    // A generator algorithm for the RAM zkSNARK.
    // Given a RAM constraint system CS, this algorithm produces proving and verification keys for CS.
    m.def("ram_zksnark_generator", &ram_zksnark_generator<ram_zksnark_ppT>);

    // A prover algorithm for the R1CS RAM zkSNARK.
    m.def("ram_zksnark_prover", &ram_zksnark_prover<ram_zksnark_ppT>);

    //  A verifier algorithm for the RAM zkSNARK.
    m.def("ram_zksnark_verifier", &ram_zksnark_verifier<ram_zksnark_ppT>);
}

void init_zk_proof_systems_zksnark_ram_zksnark_ram_zksnark(py::module &m)
{
    declare_ram_zksnark_proving_key(m);
    declare_ram_zksnark_verification_key(m);
    declare_ram_zksnark_keypair(m);
    declare_ram_zksnark_proof(m);
    declare_RAM_zksnark_Main_Algorithms(m);
}