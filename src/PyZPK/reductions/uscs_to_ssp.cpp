#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/reductions/uscs_to_ssp/uscs_to_ssp.hpp>
using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for a USCS-to-SSP reduction
void init_reductions_uscs_to_ssp(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    // Instance map for the USCS-to-SSP reduction.
    m.def("uscs_to_ssp_instance_map", &uscs_to_ssp_instance_map<FieldT>, py::arg("cs"));

    // Instance map for the USCS-to-SSP reduction followed by evaluation of the resulting SSP instance.
    m.def("uscs_to_ssp_instance_map_with_evaluation", &uscs_to_ssp_instance_map_with_evaluation<FieldT>,
          py::arg("cs"), py::arg("t"));

    // Witness map for the USCS-to-SSP reduction.
    // The witness map takes zero knowledge into account when d is random.
    m.def("uscs_to_ssp_witness_map", &uscs_to_ssp_witness_map<FieldT>,
          py::arg("cs"), py::arg("primary_input"), py::arg("auxiliary_input"),
          py::arg("d"));
}