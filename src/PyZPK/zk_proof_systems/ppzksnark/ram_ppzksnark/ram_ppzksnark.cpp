#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/ram_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/ram_ppzksnark/ram_ppzksnark.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/ram_ppzksnark/ram_ppzksnark_params.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a ppzkSNARK for RAM.

//  This includes:
//  - the class for a proving key;
//  - the class for a verification key;
//  - the class for a key pair (proving key & verification key);
//  - the class for a proof;
//  - the generator algorithm;
//  - the prover algorithm;
//  - the verifier algorithm.

void declare_ram_ppzksnark_proving_key(py::module &m)
{
    // A proving key for the RAM ppzkSNARK.
    using ppT = default_ram_ppzksnark_pp;

    py::class_<ram_ppzksnark_proving_key<ppT>>(m, "ram_ppzksnark_proving_key")
        .def(py::init<>())
        .def(py::init<const ram_ppzksnark_proving_key<ppT> &>())
        .def(
            "__eq__", [](ram_ppzksnark_proving_key<ppT> const &self, ram_ppzksnark_proving_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](ram_ppzksnark_proving_key<ppT> const &pk) {
            std::ostringstream os;
            os << pk.r1cs_pk;
            os << pk.ap;
            os << pk.primary_input_size_bound << "\n";
            os << pk.time_bound << "\n";
            return os;
        })
        .def("__istr__", [](ram_ppzksnark_proving_key<ppT> &pk) {
            std::istringstream in;
            in >> pk.r1cs_pk;
            in >> pk.ap;
            in >> pk.primary_input_size_bound;
            libff::consume_newline(in);
            in >> pk.time_bound;
            libff::consume_newline(in);
            return in;
        });
}

void declare_ram_ppzksnark_verification_key(py::module &m)
{
    // A verification key for the RAM ppzkSNARK.
    using ppT = default_ram_ppzksnark_pp;

    py::class_<ram_ppzksnark_verification_key<ppT>>(m, "ram_ppzksnark_verification_key")
        .def(py::init<>())
        .def(py::init<const ram_ppzksnark_verification_key<ppT> &>())
        .def("bind_primary_input", &ram_ppzksnark_verification_key<ppT>::bind_primary_input)
        .def(
            "__eq__", [](ram_ppzksnark_verification_key<ppT> const &self, ram_ppzksnark_verification_key<ppT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](ram_ppzksnark_verification_key<ppT> const &vk) {
            std::ostringstream os;
            os << vk.r1cs_vk;
            os << vk.ap;
            os << vk.primary_input_size_bound << "\n";
            os << vk.time_bound << "\n";
            return os;
        })
        .def("__istr__", [](ram_ppzksnark_verification_key<ppT> &vk) {
            std::istringstream in;
            in >> vk.r1cs_vk;
            in >> vk.ap;
            in >> vk.primary_input_size_bound;
            libff::consume_newline(in);
            in >> vk.time_bound;
            libff::consume_newline(in);
            return in;
        });
}

void declare_ram_ppzksnark_keypair(py::module &m)
{
    // A key pair for the RAM ppzkSNARK, which consists of a proving key and a verification key.
    using ppT = default_ram_ppzksnark_pp;

    py::class_<ram_ppzksnark_keypair<ppT>>(m, "ram_ppzksnark_keypair")
        .def(py::init<>())
        .def(py::init<const ram_ppzksnark_keypair<ppT> &>());
}

void declare_RAM_Main_Algorithms(py::module &m)
{
    using ppT = default_ram_ppzksnark_pp;

    m.def("ram_ppzksnark_generator", &ram_ppzksnark_generator<ppT>, "A generator algorithm for the RAM ppzkSNARK.", py::arg("ram_ppzksnark_architecture_params"), py::arg("primary_input_size_bound"), py::arg("time_bound"));

    m.def("ram_ppzksnark_prover", &ram_ppzksnark_prover<ppT>, "A prover algorithm for the RAM ppzkSNARK.", py::arg("ram_ppzksnark_proving_key"), py::arg("primary_input"), py::arg("auxiliary_input"));

    m.def("ram_ppzksnark_verifier", &ram_ppzksnark_verifier<ppT>, "A verifier algorithm for the RAM ppzkSNARK", py::arg("ram_ppzksnark_verification_key"), py::arg("primary_input"), py::arg("proof"));
}

void init_zk_proof_systems_ppzksnark_ram_ppzksnark_ram_ppzksnark(py::module &m)
{
    declare_ram_ppzksnark_proving_key(m);
    declare_ram_ppzksnark_verification_key(m);
    declare_ram_ppzksnark_keypair(m);
    declare_RAM_Main_Algorithms(m);
}