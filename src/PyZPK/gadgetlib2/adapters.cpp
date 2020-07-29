#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <libsnark/gadgetlib2/adapters.hpp>

namespace py = pybind11;
using namespace gadgetlib2;
using gadgetlib2::LinearTerm;
using gadgetlib2::LinearCombination;
using gadgetlib2::Constraint;
using gadgetlib2::ConstraintSystem;
using gadgetlib2::VariableAssignment;
using gadgetlib2::Protoboard;
using gadgetlib2::FElem;


void init_gadgetlib2_adapters(py::module &m)
{
    typedef unsigned long variable_index_t;
    typedef gadgetlib2::Fp Fp_elem_t;
    typedef ::std::pair<variable_index_t, Fp_elem_t> linear_term_t;
    typedef ::std::vector<linear_term_t> sparse_vec_t;
    typedef ::std::pair<sparse_vec_t, Fp_elem_t> linear_combination_t;
    typedef ::std::tuple<linear_combination_t,
                         linear_combination_t,
                         linear_combination_t> constraint_t;
    typedef ::std::vector<constraint_t> constraint_sys_t;
    typedef ::std::map<variable_index_t, Fp_elem_t> assignment_t;
    typedef ::std::pair<constraint_sys_t, assignment_t> protoboard_t;
    py::class_<GadgetLibAdapter>(m, "GadgetLibAdapter")
        .def(py::init<>())
        .def("convert", static_cast<linear_term_t (GadgetLibAdapter::*)(const LinearTerm &) const>(&GadgetLibAdapter::convert))
        .def("convert", static_cast<linear_combination_t (GadgetLibAdapter::*)(const LinearCombination &) const>(&GadgetLibAdapter::convert))
        .def("convert", static_cast<constraint_t (GadgetLibAdapter::*)(const Constraint &) const>(&GadgetLibAdapter::convert))
        .def("convert", static_cast<constraint_sys_t (GadgetLibAdapter::*)(const ConstraintSystem &) const>(&GadgetLibAdapter::convert))
        .def("convert", static_cast<assignment_t (GadgetLibAdapter::*)(const VariableAssignment &) const>(&GadgetLibAdapter::convert))
        .def("convert", static_cast<protoboard_t (GadgetLibAdapter::*)(const Protoboard &) const>(&GadgetLibAdapter::convert))
        // .def("convert", static_cast<linear_term_t (GadgetLibAdapter::*)(const FElem) const>(&GadgetLibAdapter::convert))
        .def_static("resetVariableIndex", &GadgetLibAdapter::resetVariableIndex)
        .def_static("getNextFreeIndex", &GadgetLibAdapter::getNextFreeIndex)
        .def_static("getVariableIndex", &GadgetLibAdapter::getVariableIndex);
}