#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/compliance_predicate/compliance_predicate.hpp>
#include <libsnark/zk_proof_systems/pcd/r1cs_pcd/r1cs_pcd_params.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Interfaces for a compliance predicate for R1CS PCD.
//  A compliance predicate specifies a local invariant to be enforced, by PCD,
//  throughout a dynamic distributed computation. A compliance predicate
//  receives input messages, local data, and an output message (and perhaps some
//  other auxiliary information), and then either accepts or rejects.

void declare_r1cs_pcd_message(py::module &m)
{
    // A message for R1CS PCD.
    // It is a pair, consisting of
    // - a type (a positive integer), and
    // - a payload (a vector of field elements).

    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<r1cs_pcd_message<FieldT>>(m, "r1cs_pcd_message")
        .def("payload_as_r1cs_variable_assignment", &r1cs_pcd_message<FieldT>::payload_as_r1cs_variable_assignment)
        .def("as_r1cs_variable_assignment", &r1cs_pcd_message<FieldT>::as_r1cs_variable_assignment)
        .def("print", &r1cs_pcd_message<FieldT>::print);
}

void declare_r1cs_pcd_local_data(py::module &m)
{
    // A local data for R1CS PCD.
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<r1cs_pcd_local_data<FieldT>>(m, "r1cs_pcd_local_data")
        .def("as_r1cs_variable_assignment", &r1cs_pcd_local_data<FieldT>::as_r1cs_variable_assignment);
}

void declare_r1cs_pcd_compliance_predicate(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<r1cs_pcd_compliance_predicate<FieldT>>(m, "r1cs_pcd_compliance_predicate")
        .def(py::init<>())
        .def(py::init<const r1cs_pcd_compliance_predicate<FieldT> &>())
        .def(py::init<const size_t,
                      const size_t,
                      const r1cs_constraint_system<FieldT> &,
                      const size_t,
                      const size_t,
                      const std::vector<size_t> &,
                      const size_t,
                      const size_t,
                      const bool>())
        .def("is_well_formed", &r1cs_pcd_compliance_predicate<FieldT>::is_well_formed)
        .def("has_equal_input_and_output_lengths", &r1cs_pcd_compliance_predicate<FieldT>::has_equal_input_and_output_lengths)
        .def("has_equal_input_lengths", &r1cs_pcd_compliance_predicate<FieldT>::has_equal_input_lengths)
        .def("is_satisfied", &r1cs_pcd_compliance_predicate<FieldT>::is_satisfied,
             py::arg("outgoing_message"), py::arg("incoming_messages"), py::arg("local_data"), py::arg("witness"))
        .def(
            "__eq__", [](r1cs_pcd_compliance_predicate<FieldT> const &self, r1cs_pcd_compliance_predicate<FieldT> const &other) { return self == other; }, py::is_operator())
        .def("__ostr__", [](r1cs_pcd_compliance_predicate<FieldT> const &self) {
            std::ostringstream os;
            os << self.name << "\n";
            os << self.type << "\n";
            os << self.max_arity << "\n";
            assert(self.max_arity == self.incoming_message_payload_lengths.size());
            for (size_t i = 0; i < self.max_arity; ++i)
            {
                os << self.incoming_message_payload_lengths[i] << "\n";
            }
            os << self.outgoing_message_payload_length << "\n";
            os << self.local_data_length << "\n";
            os << self.witness_length << "\n";
            libff::output_bool(os, self.relies_on_same_type_inputs);
            libff::operator<<(os, self.accepted_input_types);
            os << "\n"
               << self.constraint_system << "\n";
            return os;
        })
        .def("__istr__", [](r1cs_pcd_compliance_predicate<FieldT> &self) {
            std::istringstream in;
            in >> self.name;
            libff::consume_newline(in);
            in >> self.type;
            libff::consume_newline(in);
            in >> self.max_arity;
            libff::consume_newline(in);
            self.incoming_message_payload_lengths.resize(self.max_arity);
            for (size_t i = 0; i < self.max_arity; ++i)
            {
                in >> self.incoming_message_payload_lengths[i];
                libff::consume_newline(in);
            }
            in >> self.outgoing_message_payload_length;
            libff::consume_newline(in);
            in >> self.local_data_length;
            libff::consume_newline(in);
            in >> self.witness_length;
            libff::consume_newline(in);
            libff::input_bool(in, self.relies_on_same_type_inputs);
            libff::operator>>(in, self.accepted_input_types);
            libff::consume_newline(in);
            in >> self.constraint_system;
            libff::consume_newline(in);
            return in;
        });
}

void init_zk_proof_systems_pcd_r1cs_pcd_compliance_predicate(py::module &m)
{
    declare_r1cs_pcd_message(m);
    declare_r1cs_pcd_local_data(m);
    declare_r1cs_pcd_compliance_predicate(m);
}