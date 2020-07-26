#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <libsnark/gadgetlib2/protoboard.hpp>

namespace py = pybind11;
using namespace gadgetlib2;

// Declaration of PublicParams for Fp field arithmetic
void init_gadgetlib2_Protoboard(py::module &m)
{
    py::class_<Protoboard>(m, "Protoboard")
        .def_readonly("fieldType_", &Protoboard::fieldType_)
        .def_static("create", &Protoboard::create)
        .def("numVars", &Protoboard::numVars)
        .def("numInputs", &Protoboard::numInputs)
        .def("params", &Protoboard::params)
        .def("val", py::overload_cast<const Variable&>(&Protoboard::val))
        .def("setValuesAsBitArray", &Protoboard::setValuesAsBitArray)
        .def("setDualWordValue", &Protoboard::setDualWordValue)
        .def("setMultipackedWordValue", &Protoboard::setMultipackedWordValue)
        .def("addRank1Constraint", &Protoboard::addRank1Constraint)
        .def("addGeneralConstraint", &Protoboard::addGeneralConstraint)
        .def("addUnaryConstraint", &Protoboard::addUnaryConstraint)
        .def("isSatisfied", &Protoboard::isSatisfied)
        .def("flagIsSet", &Protoboard::flagIsSet)
        .def("setFlag", &Protoboard::setFlag)
        .def("clearFlag", &Protoboard::clearFlag)
        .def("flipFlag", &Protoboard::flipFlag)
        .def("enforceBooleanity", &Protoboard::enforceBooleanity)
        .def("annotation", &Protoboard::annotation)
        .def("constraintSystem", &Protoboard::constraintSystem)
        .def("assignment", &Protoboard::assignment)
        .def("dualWordAssignmentEqualsValue", &Protoboard::dualWordAssignmentEqualsValue)
        .def("multipackedWordAssignmentEqualsValue", &Protoboard::multipackedWordAssignmentEqualsValue)
        .def("unpackedWordAssignmentEqualsValue", &Protoboard::unpackedWordAssignmentEqualsValue);
}