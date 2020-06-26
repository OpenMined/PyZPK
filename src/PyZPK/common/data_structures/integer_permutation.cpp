#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <libsnark/common/data_structures/integer_permutation.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

void init_data_structures_integer_permutation(py::module &m)
{
    // Binding for common/data_structures/integer_permutation.cpp
    py::class_<integer_permutation>(m, "integer_permutation")
        .def(py::init<const size_t>())
        .def(py::init<const size_t, const size_t>())
        .def("set", &integer_permutation::set, py::arg("position"), py::arg("value"))
        .def("get", &integer_permutation::get, py::arg("position"))
        .def("size", &integer_permutation::size)
        .def("is_valid", &integer_permutation::is_valid)
        .def("inverse", &integer_permutation::inverse)
        .def("slice", &integer_permutation::slice, py::arg("slice_min_element"), py::arg("slice_max_element"))
        .def("next_permutation", &integer_permutation::next_permutation)
        .def("random_shuffle", &integer_permutation::random_shuffle)
        .def(
            "__eq__", [](integer_permutation const &self, integer_permutation const &other) { return self == other; }, py::is_operator());
}