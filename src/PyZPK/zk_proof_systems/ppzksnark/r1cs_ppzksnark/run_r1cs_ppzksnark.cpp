#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/examples/run_r1cs_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_zk_proof_systems_ppzksnark_r1cs_ppzksnark_run_r1cs_ppzksnark(py::module &m)
{
    // Runs the ppzkSNARK (generator, prover, and verifier) for a given
    // R1CS example (specified by a constraint system, input, and witness).

    using ppT = mnt6_pp;
    m.def("run_r1cs_ppzksnark", &run_r1cs_ppzksnark<ppT>, py::arg("example"), py::arg("test_serialization"));
}