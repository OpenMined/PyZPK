#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/common/default_types/r1cs_ppzkpcd_pp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_mp_ppzkpcd/examples/run_r1cs_mp_ppzkpcd.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;


//  Declaration of functionality that runs the R1CS multi-predicate ppzkPCD
//  for a compliance predicate example.
void init_zk_proof_systems_pcd_r1cs_pcd_r1cs_mp_ppzkpcd_run_r1cs_mp_ppzkpcd_tally_example(py::module &m)
{
    using PCD_ppT = default_r1cs_ppzkpcd_pp;

    // Runs the multi-predicate ppzkPCD (generator, prover, and verifier) for the 
    // "tally compliance predicate", of a given wordsize, arity, and depth.
    // Optionally, also test the serialization routines for keys and proofs. (This takes additional time.) 
    // Optionally, also test the case of compliance predicates with different types.
    m.def("run_r1cs_mp_ppzkpcd_tally_example", &run_r1cs_mp_ppzkpcd_tally_example<PCD_ppT>);
}