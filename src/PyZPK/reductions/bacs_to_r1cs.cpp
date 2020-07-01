#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/reductions/bacs_to_r1cs/bacs_to_r1cs.hpp>
using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a BACS-to-R1CS reduction, that is, constructing
// a R1CS ("Rank-1 Constraint System") from a BACS ("Bilinear Arithmetic Circuit Satisfiability").

// Each bilinear gate gives rises to a corresponding R1CS constraint that enforces correct 
// computation of the gate; also, each output gives rise to a corresponding R1CS constraint that enforces
// that the output is zero.
void init_reductions_bacs_to_r1cs(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    // Instance map for the BACS-to-R1CS reduction.
    m.def("bacs_to_r1cs_instance_map", &bacs_to_r1cs_instance_map<FieldT>, py::arg("circuit"));

    // Witness map for the BACS-to-R1CS reduction.
    m.def("bacs_to_r1cs_witness_map", &bacs_to_r1cs_witness_map<FieldT>,
          py::arg("circuit"), py::arg("primary_input"), py::arg("auxiliary_input"));
}