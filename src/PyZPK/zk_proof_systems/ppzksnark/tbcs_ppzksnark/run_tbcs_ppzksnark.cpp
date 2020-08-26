#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/tbcs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/tbcs_ppzksnark/examples/run_tbcs_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Declaration of functionality that runs the TBCS ppzkSNARK for a given TBCS example.
void init_zk_proof_systems_ppzksnark_tbcs_ppzksnark_run_tbcs_ppzksnark(py::module &m)
{
    // Runs the ppzkSNARK (generator, prover, and verifier) for a given
    // TBCS example (specified by an architecture, boot trace, auxiliary input, and time bound).

    using ppT = default_tbcs_ppzksnark_pp;
    m.def("run_tbcs_ppzksnark", &run_tbcs_ppzksnark<ppT>, py::arg("example"), py::arg("test_serialization"));
}