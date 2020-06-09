#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libfqfft/evaluation_domain/evaluation_domain.hpp>
#include <libsnark/relations/arithmetic_programs/sap/sap.hpp>
#define FieldT libff::Fr<libff::mnt6_pp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

// Implementation of interfaces for a SAP ("Square Arithmetic Program").
void init_relations_arithmetic_programs_sap(py::module &m)
{
    // A SAP instance.
    py::class_<sap_instance<FieldT>>(m, "sap_instance")
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const std::vector<std::map<size_t, FieldT>> &,
                      const std::vector<std::map<size_t, FieldT>> &>())
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      std::vector<std::map<size_t, FieldT>> &,
                      std::vector<std::map<size_t, FieldT>> &>())
        .def("num_variables", &sap_instance<FieldT>::num_variables)
        .def("degree", &sap_instance<FieldT>::degree)
        .def("num_inputs", &sap_instance<FieldT>::num_inputs)
        .def("is_satisfied", &sap_instance<FieldT>::is_satisfied, py::arg("witness"));

    // A SAP instance evaluation is a SAP instance that is evaluated at a field element t.
    py::class_<sap_instance_evaluation<FieldT>>(m, "sap_instance_evaluation")
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
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
                      const FieldT &>())
        .def("num_variables", &sap_instance_evaluation<FieldT>::num_variables)
        .def("degree", &sap_instance_evaluation<FieldT>::degree)
        .def("num_inputs", &sap_instance_evaluation<FieldT>::num_inputs)
        .def("is_satisfied", &sap_instance_evaluation<FieldT>::is_satisfied, py::arg("witness"));

    //A SAP witness.
    py::class_<sap_witness<FieldT>>(m, "sap_witness")
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      const FieldT &,
                      const std::vector<FieldT> &,
                      const std::vector<FieldT> &>())
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      const FieldT &,
                      const std::vector<FieldT> &,
                      std::vector<FieldT> &>())
        .def("num_variables", &sap_witness<FieldT>::num_variables)
        .def("degree", &sap_witness<FieldT>::degree)
        .def("num_inputs", &sap_witness<FieldT>::num_inputs);
        
    m.attr("mnt6_Fr_s") = 17;
}