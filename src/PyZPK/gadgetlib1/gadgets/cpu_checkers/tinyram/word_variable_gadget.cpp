#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/cpu_checkers/tinyram/components/word_variable_gadget.hpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

// Interfaces for (single and double) word gadgets.
void declare_tinyram_word_variable_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<word_variable_gadget<FieldT>, dual_variable_gadget<FieldT>>(m, "word_variable_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &, const std::string &>())
        .def(py::init<tinyram_protoboard<FieldT> &, const pb_variable_array<FieldT> &, const std::string &>())
        .def(py::init<tinyram_protoboard<FieldT> &, const pb_variable<FieldT> &, const std::string &>());
}

void declare_tinyram_doubleword_variable_gadget(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    py::class_<doubleword_variable_gadget<FieldT>, dual_variable_gadget<FieldT>>(m, "doubleword_variable_gadget")
        .def(py::init<tinyram_protoboard<FieldT> &, const std::string &>())
        .def(py::init<tinyram_protoboard<FieldT> &, const pb_variable_array<FieldT> &, const std::string &>())
        .def(py::init<tinyram_protoboard<FieldT> &, const pb_variable<FieldT> &, const std::string &>());
}

void init_gadgetlib1_tinyram_word_variable_gadget(py::module &m)
{
    declare_tinyram_word_variable_gadget(m);
    declare_tinyram_doubleword_variable_gadget(m);
}
