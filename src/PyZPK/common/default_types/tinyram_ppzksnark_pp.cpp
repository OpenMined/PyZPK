#include <pybind11/pybind11.h>
#include <libsnark/common/default_types/tinyram_ppzksnark_pp.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

void init_default_types_tinyram_ppzksnark_pp(py::module &m)
{
    // Binding for #include common/default_types/tinyram_ppzksnark_pp.hpp
    py::class_<default_tinyram_ppzksnark_pp>(m, "default_tinyram_ppzksnark_pp")
        .def_static("init_public_params", &default_tinyram_ppzksnark_pp::init_public_params);
}