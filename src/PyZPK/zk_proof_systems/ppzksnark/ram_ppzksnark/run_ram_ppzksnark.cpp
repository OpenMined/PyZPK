#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/ram_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/ram_ppzksnark/examples/run_ram_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Declaration of functionality that runs the RAM ppzkSNARK for a given RAM example.
void init_zk_proof_systems_ppzksnark_ram_ppzksnark_run_ram_ppzksnark(py::module &m)
{
    // Runs the ppzkSNARK (generator, prover, and verifier) for a given
    // RAM example (specified by an architecture, boot trace, auxiliary input, and time bound).

    using ppT = default_ram_ppzksnark_pp;
    m.def("run_ram_ppzksnark", &run_ram_ppzksnark<ppT>, py::arg("example"), py::arg("test_serialization"));
}