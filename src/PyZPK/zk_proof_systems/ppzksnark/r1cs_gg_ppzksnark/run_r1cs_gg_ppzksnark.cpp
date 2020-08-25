#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/examples/run_r1cs_gg_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Declaration of functionality that runs the R1CS GG ppzkSNARK for
// a given R1CS example.

void init_zk_proof_systems_ppzksnark_r1cs_gg_ppzksnark_run_r1cs_gg_ppzksnark(py::module &m)
{
    // Runs the GG ppzkSNARK(generator, prover, and verifier) for a given
    // R1CS example(specified by a constraint system, input, and witness).

    using ppT = default_r1cs_gg_ppzksnark_pp;

    m.def("run_r1cs_gg_ppzksnark", &run_r1cs_gg_ppzksnark<ppT>, py::arg("example"), py::arg("test_serialization"));
}