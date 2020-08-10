#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/common/default_types/r1cs_ppzkadsnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzkadsnark/r1cs_ppzkadsnark/r1cs_ppzkadsnark_params.hpp>
#include <libsnark/zk_proof_systems/ppzkadsnark/r1cs_ppzkadsnark/r1cs_ppzkadsnark_prf.hpp>
#include <libsnark/zk_proof_systems/ppzkadsnark/r1cs_ppzkadsnark/r1cs_ppzkadsnark_signature.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void declare_r1cs_ppzkadsnark_params(py::module &m)
{
    // Public-parameter selector for the R1CS ppzkADSNARK.

    py::class_<labelT>(m, "labelT")
        .def(py::init<>());
}

void declare_r1cs_ppzkadsnark_signature(py::module &m)
{
    //  Generic signature interface for ADSNARK.
    using ppT = default_r1cs_ppzkadsnark_pp;

    py::class_<kpT<ppT>>(m, "kpT");
}

void init_zk_proof_systems_ppzkadsnark_r1cs_ppzkadsnark_params_prf_signature(py::module &m)
{
    declare_r1cs_ppzkadsnark_params(m);
    declare_r1cs_ppzkadsnark_signature(m);
}