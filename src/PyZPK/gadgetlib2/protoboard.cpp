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
        .def_static("create", &Protoboard::create, py::arg("fieldType"), py::arg("pParams"))
        .def("numVars", &Protoboard::numVars)
        .def("numInputs", &Protoboard::numInputs)
        .def("params", &Protoboard::params)
        .def("val", py::overload_cast<const Variable&>(&Protoboard::val), py::arg("Variable"))
        .def("setValuesAsBitArray", &Protoboard::setValuesAsBitArray, py::arg("VariableArray"), py::arg("srcValue"))
        .def("setDualWordValue", &Protoboard::setDualWordValue, py::arg("DualWord"), py::arg("srcValue"))
        .def("setMultipackedWordValue", &Protoboard::setMultipackedWordValue, py::arg("MultiPackedWord"), py::arg("srcValue"))
        .def("addRank1Constraint", &Protoboard::addRank1Constraint, py::arg("LinearCombination_a"), py::arg("LinearCombination_b"), py::arg("LinearCombination_c"), py::arg("name"))
        .def("addGeneralConstraint", &Protoboard::addGeneralConstraint, py::arg("Polynomial_a"), py::arg("Polynomial_b"), py::arg("name"))
        .def("addUnaryConstraint", &Protoboard::addUnaryConstraint, py::arg("LinearCombination"), py::arg("name"))
        .def("isSatisfied", &Protoboard::isSatisfied, py::arg("LinearCombination"))
        .def("flagIsSet", &Protoboard::flagIsSet, py::arg("FlagVariable"))
        .def("setFlag", &Protoboard::setFlag)
        .def("clearFlag", &Protoboard::clearFlag, py::arg("FlagVariable"))
        .def("flipFlag", &Protoboard::flipFlag, py::arg("FlagVariable"))
        .def("enforceBooleanity", &Protoboard::enforceBooleanity, py::arg("Variable"))
        .def("annotation", &Protoboard::annotation)
        .def("constraintSystem", &Protoboard::constraintSystem)
        .def("assignment", &Protoboard::assignment)
        .def("dualWordAssignmentEqualsValue", &Protoboard::dualWordAssignmentEqualsValue, py::arg("DualWord"), py::arg("expectedValue"), py::arg("PrintOptions"))
        .def("multipackedWordAssignmentEqualsValue", &Protoboard::multipackedWordAssignmentEqualsValue, py::arg("MultiPackedWord"), py::arg("expectedValue"), py::arg("PrintOptions"))
        .def("unpackedWordAssignmentEqualsValue", &Protoboard::unpackedWordAssignmentEqualsValue, py::arg("UnpackedWord"), py::arg("expectedValue"), py::arg("PrintOptions"));

        py::class_<ProtoboardParams>(m, "ProtoboardParams");
}