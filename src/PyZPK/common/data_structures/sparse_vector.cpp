#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/operators.h>
#include <libff/algebra/curves/public_params.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/common/data_structures/sparse_vector.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

void init_data_structures_sparse_vector(py::module &m)
{
    using ppT = mnt6_pp;
    using T = libff::G1<ppT>;
    py::class_<sparse_vector<T>>(m, "sparse_vector")
        .def(py::init<>())
        .def(py::init<const sparse_vector<T> &>())
        .def("is_valid", &sparse_vector<T>::is_valid)
        .def("empty", &sparse_vector<T>::empty)
        .def("domain_size", &sparse_vector<T>::domain_size, "return domain_size_")
        .def("size", &sparse_vector<T>::size, "return the number of indices (representing the number of non-zero entries)")
        .def("size_in_bits", &sparse_vector<T>::size_in_bits, "return the number bits needed to store the sparse vector")
        .def(
            "__eq__", [](sparse_vector<T> const &self, sparse_vector<T> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](sparse_vector<T> const &v) {
            std::ostringstream out;
            out << v.domain_size_ << "\n";
            out << v.indices.size() << "\n";
            for (const size_t &i : v.indices)
            {
                out << i << "\n";
            }
            out << v.values.size() << "\n";
            for (const T &t : v.values)
            {
                out << t << OUTPUT_NEWLINE;
            }
            return out;
        })
        .def("__istr__", [](sparse_vector<T> &v) {
            std::istringstream in;
            in >> v.domain_size_;
            libff::consume_newline(in);
            size_t s;
            in >> s;
            libff::consume_newline(in);
            v.indices.resize(s);
            for (size_t i = 0; i < s; ++i)
            {
                in >> v.indices[i];
                libff::consume_newline(in);
            }
            v.values.clear();
            in >> s;
            libff::consume_newline(in);
            v.values.reserve(s);

            for (size_t i = 0; i < s; ++i)
            {
                T t;
                in >> t;
                libff::consume_OUTPUT_NEWLINE(in);
                v.values.emplace_back(t);
            }
            return in;
        });
}