#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/ram_zksnark_pp.hpp>
#include <libsnark/zk_proof_systems/zksnark/ram_zksnark/examples/run_ram_zksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Declaration of functionality that runs the RAM zkSNARK for
//  a given RAM example.

void init_zk_proof_systems_ppzksnark_ram_zksnark_run_ram_zksnark(py::module &m)
{
    // Runs the zkSNARK (generator, prover, and verifier) for a given
    // RAM example (specified by an architecture, boot trace, auxiliary input, and time bound).

    using ram_zksnark_ppT = default_ram_zksnark_pp;

    m.def("run_ram_zksnark", &run_ram_zksnark<ram_zksnark_ppT>, py::arg("example"), py::arg("test_serialization"));
}