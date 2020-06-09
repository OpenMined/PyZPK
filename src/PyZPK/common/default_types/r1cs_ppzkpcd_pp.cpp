#include <pybind11/pybind11.h>
#include <libsnark/common/default_types/r1cs_ppzkpcd_pp.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

void init_default_types_r1cs_ppzkpcd_pp(py::module &m)
{
    // Binding for #include common/default_types/r1cs_ppzkpcd_pp.hpp
    py::class_<default_r1cs_ppzkpcd_pp>(m, "default_r1cs_ppzkpcd_pp")
        .def_static("init_public_params", &default_r1cs_ppzkpcd_pp::init_public_params);
}