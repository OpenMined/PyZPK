#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/knowledge_commitment/knowledge_commitment.hpp>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//   A knowledge commitment is a pair (g,h) where g is in T1 and h in T2,
//   and T1 and T2 are groups (written additively).
//   Such pairs form a group by defining:
//   - "zero" = (0,0)
//   - "one" = (1,1)
//   - a * (g,h) + b * (g',h') := ( a * g + b * g', a * h + b * h').

void init_knowledge_commitment_knowledge_commitment(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;
    using T1 = libff::G1<ppT>;
    using T2 = libff::G1<ppT>;

    py::class_<knowledge_commitment<T1, T2>>(m, "knowledge_commitment")
        .def(py::init<>())
        .def(py::init<const knowledge_commitment<T1, T2> &>())
        .def(py::init<const T1 &, const T2 &>())
        .def_readwrite("g", &knowledge_commitment<T1, T2>::g)
        .def_readwrite("h", &knowledge_commitment<T1, T2>::h)
        .def("mixed_add", &knowledge_commitment<T1, T2>::mixed_add)
        .def("dbl", &knowledge_commitment<T1, T2>::dbl)
        .def("to_special", &knowledge_commitment<T1, T2>::to_special)
        .def("is_zero", &knowledge_commitment<T1, T2>::is_zero)
        .def("print", &knowledge_commitment<T1, T2>::print)
        .def_static("size_in_bits", &knowledge_commitment<T1, T2>::size_in_bits)
        .def_static("zero", &knowledge_commitment<T1, T2>::zero)
        .def_static("one", &knowledge_commitment<T1, T2>::one)
        .def_static("size_in_bits", &knowledge_commitment<T1, T2>::size_in_bits)
        .def_static("batch_to_special_all_non_zeros", &knowledge_commitment<T1, T2>::batch_to_special_all_non_zeros)
        .def(py::self + py::self)
        .def(bigint<5l>() * py::self)
        .def(FieldT() * py::self)
        .def(
            "__eq__", [](knowledge_commitment<T1, T2> const &self, knowledge_commitment<T1, T2> const &other) { return self == other; }, py::is_operator())
        .def(
            "__ne__", [](knowledge_commitment<T1, T2> const &self, knowledge_commitment<T1, T2> const &other) { return self != other; }, py::is_operator())
        .def("__ostr__", [](knowledge_commitment<T1, T2> const &self) {
            std::ostringstream os;
            os << self.g << OUTPUT_SEPARATOR << self.h;
            return os;
        })
        .def("__istr__", [](knowledge_commitment<T1, T2> &self) {
            std::istringstream in;
            in >> self.g;
            libff::consume_OUTPUT_SEPARATOR(in);
            in >> self.h;
            return in;
        });
}
