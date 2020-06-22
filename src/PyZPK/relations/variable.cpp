#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/cast.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/relations/variable.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for a variable (i.e., x_i),
// a linear term (i.e., a_i * x_i), and
// a linear combination (i.e., sum_i a_i * x_i).
void init_relations_variable(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    // A variable represents a formal expression of the form "x_{index}".
    py::class_<variable<FieldT>>(m, "variable")
        .def(py::init<const var_index_t>())
        .def_readwrite("index", &variable<FieldT>::index)
        .def(py::self * integer_coeff_t())
        .def(py::self * FieldT())
        .def(py::self + linear_combination<FieldT>())
        .def(py::self - linear_combination<FieldT>())
        .def(-py::self)
        .def(
            "__eq__", [](variable<FieldT> const &self, variable<FieldT> const &other) { return self == other; }, py::is_operator());

    // A linear term represents a formal expression of the form "coeff * x_{index}".
    py::class_<linear_term<FieldT>>(m, "linear_term")
        .def(py::init<>())
        .def(py::init<const variable<FieldT>>())
        .def(py::init<const variable<FieldT> &, const integer_coeff_t>())
        .def(py::init<const variable<FieldT> &, const FieldT &>())
        .def_readwrite("index", &linear_term<FieldT>::index)
        .def_readwrite("coeff", &linear_term<FieldT>::coeff)
        .def(py::self * integer_coeff_t())
        .def(py::self * FieldT())
        .def(py::self + linear_combination<FieldT>())
        .def(py::self - linear_combination<FieldT>())
        .def(-py::self)
        .def(
            "__eq__", [](linear_term<FieldT> const &self, linear_term<FieldT> const &other) { return self == other; }, py::is_operator());

    // A linear combination represents a formal expression of the form "sum_i coeff_i * x_{index_i}".
    py::class_<linear_combination<FieldT>>(m, "linear_combination")
        .def(py::init<>())
        .def(py::init<const integer_coeff_t>())
        .def(py::init<const FieldT &>())
        .def(py::init<const variable<FieldT> &>())
        .def(py::init<const linear_term<FieldT> &>())
        .def(py::init<const std::vector<linear_term<FieldT>> &>())
        .def_readwrite("terms", &linear_combination<FieldT>::terms)
        .def("add_term", py::overload_cast<const variable<FieldT> &>(&linear_combination<FieldT>::add_term), py::arg("var"))
        .def("add_term", py::overload_cast<const variable<FieldT> &, const integer_coeff_t>(&linear_combination<FieldT>::add_term), py::arg("var"), py::arg("int_coeff"))
        .def("add_term", py::overload_cast<const variable<FieldT> &, const FieldT &>(&linear_combination<FieldT>::add_term), py::arg("var"), py::arg("field_coeff"))
        .def("add_term", py::overload_cast<const linear_term<FieldT> &>(&linear_combination<FieldT>::add_term), py::arg("lt"))
        .def("evaluate", &linear_combination<FieldT>::evaluate, py::arg("assignment"))
        .def(py::self * integer_coeff_t())
        .def(py::self * FieldT())
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(-py::self)
        .def(
            "__eq__", [](linear_combination<FieldT> const &self, linear_combination<FieldT> const &other) { return self == other; }, py::is_operator())
        .def("is_valid", &linear_combination<FieldT>::is_valid, py::arg("num_variables"))
        .def("print", &linear_combination<FieldT>::print, py::arg("variable_annotations"))
        .def("print_with_assignment", &linear_combination<FieldT>::print_with_assignment, py::arg("full_assignment"), py::arg("variable_annotations"))
        .def("__ostr__", [](linear_combination<FieldT> const &self) {
            std::ostringstream os;
            os << self.terms.size() << "\n";
            for (const linear_term<FieldT> &lt : self.terms)
            {
                os << lt.index << "\n";
                os << lt.coeff << OUTPUT_NEWLINE;
            }
            return os;
        })
        .def("__istr__", [](linear_combination<FieldT> &self) {
            std::istringstream os;
            self.terms.clear();
            size_t s;
            os >> s;
            libff::consume_newline(os);
            self.terms.reserve(s);
            for (size_t i = 0; i < s; ++i)
            {
                linear_term<FieldT> lt;
                os >> lt.index;
                libff::consume_newline(os);
                os >> lt.coeff;
                libff::consume_OUTPUT_NEWLINE(os);
                self.terms.emplace_back(lt);
            }
            return os;
        });
}
