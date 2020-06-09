#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libfqfft/evaluation_domain/evaluation_domain.hpp>
#include <libsnark/relations/arithmetic_programs/qap/qap.hpp>
#define FieldT libff::Fr<libff::mnt6_pp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

// Implementation of interfaces for a QAP ("Quadratic Arithmetic Program").
void init_relations_arithmetic_programs_qap(py::module &m)
{
    // A QAP instance.
    py::class_<qap_instance<FieldT>>(m, "qap_instance")
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const std::vector<std::map<size_t, FieldT>> &,
                      const std::vector<std::map<size_t, FieldT>> &,
                      const std::vector<std::map<size_t, FieldT>> &>())
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      std::vector<std::map<size_t, FieldT>> &,
                      std::vector<std::map<size_t, FieldT>> &,
                      std::vector<std::map<size_t, FieldT>> &>())
        .def("num_variables", &qap_instance<FieldT>::num_variables)
        .def("degree", &qap_instance<FieldT>::degree)
        .def("num_inputs", &qap_instance<FieldT>::num_inputs)
        .def("is_satisfied", &qap_instance<FieldT>::is_satisfied, py::arg("witness"));

    // A QAP instance evaluation is a QAP instance that is evaluated at a field element t.
    py::class_<qap_instance_evaluation<FieldT>>(m, "qap_instance_evaluation")
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      const std::vector<FieldT> &,
                      const std::vector<FieldT> &,
                      const std::vector<FieldT> &,
                      const std::vector<FieldT> &,
                      const FieldT &>())
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      std::vector<FieldT> &&,
                      std::vector<FieldT> &&,
                      std::vector<FieldT> &&,
                      std::vector<FieldT> &&,
                      const FieldT &>())
        .def("num_variables", &qap_instance_evaluation<FieldT>::num_variables)
        .def("degree", &qap_instance_evaluation<FieldT>::degree)
        .def("num_inputs", &qap_instance_evaluation<FieldT>::num_inputs)
        .def("is_satisfied", &qap_instance_evaluation<FieldT>::is_satisfied, py::arg("witness"));

    //A QAP witness.
    py::class_<qap_witness<FieldT>>(m, "qap_witness")
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      const FieldT &,
                      const FieldT &,
                      const std::vector<FieldT> &,
                      const std::vector<FieldT> &>())
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      const FieldT &,
                      const FieldT &,
                      const std::vector<FieldT> &,
                      std::vector<FieldT> &>())
        .def("num_variables", &qap_witness<FieldT>::num_variables)
        .def("degree", &qap_witness<FieldT>::degree)
        .def("num_inputs", &qap_witness<FieldT>::num_inputs);

    // Source: libff/algebra/curves/mnt/mnt6/mnt6_init.cpp
    // Implementation of interfaces for initializing MNT6.
    m.attr("mnt6_Fr_s") = 17;
}