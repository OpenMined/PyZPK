#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/uscs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/uscs_ppzksnark/examples/run_uscs_ppzksnark.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Declaration of functionality that runs the USCS ppzkSNARK for
//  a given USCS example.
void init_zk_proof_systems_ppzksnark_uscs_ppzksnark_run_uscs_ppzksnark(py::module &m)
{
    // Runs the ppzkSNARK (generator, prover, and verifier) for a given
    // USCS example (specified by a circuit, primary input, and auxiliary input).

    using ppT = default_uscs_ppzksnark_pp;
    m.def("run_uscs_ppzksnark", &run_uscs_ppzksnark<ppT>);
}