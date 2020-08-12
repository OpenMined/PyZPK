#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/bacs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/bacs_ppzksnark/examples/run_bacs_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Declaration of functionality that runs the BACS ppzkSNARK for
//  a given BACS example.
void init_zk_proof_systems_ppzksnark_bacs_ppzksnark_run_bacs_ppzksnark(py::module &m)
{
    // Runs the ppzkSNARK (generator, prover, and verifier) for a given
    // BACS example (specified by a circuit, primary input, and auxiliary input).

    using ppT = default_bacs_ppzksnark_pp;
    m.def("run_bacs_ppzksnark", &run_bacs_ppzksnark<ppT>);
}