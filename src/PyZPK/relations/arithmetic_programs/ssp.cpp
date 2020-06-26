#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/relations/arithmetic_programs/ssp/ssp.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Implementation of interfaces for a SSP ("Square Span Program").
void init_relations_arithmetic_programs_ssp(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;
    // A SSP instance.
    py::class_<ssp_instance<FieldT>>(m, "ssp_instance")
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const std::vector<std::map<size_t, FieldT>> &>())
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      std::vector<std::map<size_t, FieldT>> &>())
        .def("num_variables", &ssp_instance<FieldT>::num_variables)
        .def("degree", &ssp_instance<FieldT>::degree)
        .def("num_inputs", &ssp_instance<FieldT>::num_inputs)
        .def("is_satisfied", &ssp_instance<FieldT>::is_satisfied, py::arg("witness"));

    // A SSP instance evaluation is a SSP instance that is evaluated at a field element t.
    py::class_<ssp_instance_evaluation<FieldT>>(m, "ssp_instance_evaluation")
        .def(py::init<const std::shared_ptr<libfqfft::evaluation_domain<FieldT>> &,
                      const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
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
                      const FieldT &>())
        .def("num_variables", &ssp_instance_evaluation<FieldT>::num_variables)
        .def("degree", &ssp_instance_evaluation<FieldT>::degree)
        .def("num_inputs", &ssp_instance_evaluation<FieldT>::num_inputs)
        .def("is_satisfied", &ssp_instance_evaluation<FieldT>::is_satisfied, py::arg("witness"));

    //A SSP witness.
    py::class_<ssp_witness<FieldT>>(m, "ssp_witness")
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      const std::vector<FieldT> &,
                      const std::vector<FieldT> &>())
        .def(py::init<const size_t,
                      const size_t,
                      const size_t,
                      const FieldT &,
                      const std::vector<FieldT> &,
                      std::vector<FieldT> &>())
        .def("num_variables", &ssp_witness<FieldT>::num_variables)
        .def("degree", &ssp_witness<FieldT>::degree)
        .def("num_inputs", &ssp_witness<FieldT>::num_inputs);
}