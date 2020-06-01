#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <unordered_set>
#include <iostream>

#include <libff/common/serialization.hpp>
#include <libsnark/common/data_structures/integer_permutation.hpp>
#include <libsnark/common/data_structures/set_commitment.hpp>

using namespace std;
using namespace libsnark;
namespace py = pybind11;

PYBIND11_MODULE(pyzpk, m)
{
    m.doc() = "Python wrapper for open source Zero Proof Knowledge Library";

    // Binding for common/data_structures/integer_permutation.cpp
    py::class_<integer_permutation>(m, "integer_permutation")
        .def(py::init<const size_t>())
        .def(py::init<const size_t, const size_t>())
        .def("set", &integer_permutation::set)
        .def("get", &integer_permutation::get)
        .def("size", &integer_permutation::size)
        .def("is_valid", &integer_permutation::is_valid)
        .def("inverse", &integer_permutation::inverse)
        .def("slice", &integer_permutation::slice)
        .def("next_permutation", &integer_permutation::next_permutation)
        .def("random_shuffle", &integer_permutation::random_shuffle)
        .def(
            "__eq__", [](integer_permutation const &self, integer_permutation const &other) { return self == other; }, py::is_operator());

    // Binding for common/data_structures/set_commitment.cpp // set_membership_proof
    py::class_<set_membership_proof>(m, "set_membership_proof")
        .def("size_in_bits", &set_membership_proof::size_in_bits)
        .def(
            "__eq__", [](set_membership_proof const &self, set_membership_proof const &other) { return self == other; }, py::is_operator());
}
