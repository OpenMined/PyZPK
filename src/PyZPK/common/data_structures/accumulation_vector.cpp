#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/operators.h>
#include <libff/algebra/curves/public_params.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/common/data_structures/accumulation_vector.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_data_structures_accumulation_vector(py::module &m)
{
    using ppT = mnt6_pp;
    using T = libff::G1<ppT>;
    py::class_<accumulation_vector<T>>(m, "accumulation_vector")
        .def(py::init<>())
        .def(py::init<const accumulation_vector<T> &>())
        .def("is_fully_accumulated", &accumulation_vector<T>::is_fully_accumulated)
        .def("domain_size", &accumulation_vector<T>::domain_size)
        .def("size", &accumulation_vector<T>::size)
        .def("size_in_bits", &accumulation_vector<T>::size_in_bits)
        .def(
            "__eq__", [](accumulation_vector<T> const &self, accumulation_vector<T> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](accumulation_vector<T> const &v) {
            std::ostringstream out;
            out << v.first << OUTPUT_NEWLINE;
            out << v.rest << OUTPUT_NEWLINE;
            return out;
        })
        .def("__istr__", [](accumulation_vector<T> &v) {
            std::istringstream in;
            in >> v.first;
            libff::consume_OUTPUT_NEWLINE(in);
            in >> v.rest;
            libff::consume_OUTPUT_NEWLINE(in);
            return in;
        });
}