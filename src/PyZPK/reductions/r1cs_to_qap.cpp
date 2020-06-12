#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/relations/arithmetic_programs/qap/qap.hpp>
#include <libsnark/relations/constraint_satisfaction_problems/r1cs/r1cs.hpp>
#include <libsnark/reductions/r1cs_to_qap/r1cs_to_qap.hpp>
using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Implementation of interfaces for a R1CS-to-QAP reduction.
void init_reductions_r1cs_to_qap(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    // Instance map for the R1CS-to-QAP reduction.
    m.def("r1cs_to_qap_instance_map", &r1cs_to_qap_instance_map<FieldT>, py::arg("cs"));

    // Instance map for the R1CS-to-QAP reduction followed by evaluation of the resulting QAP instance.
    m.def("r1cs_to_qap_instance_map_with_evaluation", &r1cs_to_qap_instance_map_with_evaluation<FieldT>,
          py::arg("cs"), py::arg("t"));

    // Witness map for the R1CS-to-QAP reduction.
    // The witness map takes zero knowledge into account when d1,d2,d3 are random.
    m.def("r1cs_to_qap_witness_map", &r1cs_to_qap_witness_map<FieldT>,
          py::arg("cs"), py::arg("primary_input"), py::arg("auxiliary_input"),
          py::arg("d1"), py::arg("d2"), py::arg("d3"));
}