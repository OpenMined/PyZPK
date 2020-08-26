#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/common/default_types/r1cs_ppzkpcd_pp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_sp_ppzkpcd/examples/run_r1cs_sp_ppzkpcd.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Declaration of functionality that runs the R1CS single-predicate ppzkPCD
// for a compliance predicate example.
void init_zk_proof_systems_pcd_r1cs_pcd_r1cs_sp_ppzkpcd_run_r1cs_sp_ppzkpcd(py::module &m)
{
    using PCD_ppT = default_r1cs_ppzkpcd_pp;

    // Runs the single-predicate ppzkPCD (generator, prover, and verifier) for the
    // "tally compliance predicate", of a given wordsize, arity, and depth.
    m.def("run_r1cs_sp_ppzkpcd_tally_example", &run_r1cs_sp_ppzkpcd_tally_example<PCD_ppT>, py::arg("wordsize"), py::arg("arity"), py::arg("depth"), py::arg("test_serialization"));
}