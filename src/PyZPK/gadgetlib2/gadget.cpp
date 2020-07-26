#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libsnark/gadgetlib2/gadget.hpp>

namespace py = pybind11;
using namespace gadgetlib2;
// Interfaces and basic gadgets for R1P (Rank 1 prime characteristic)
// constraint systems.

// Gadget class, representing the constraints and witness generation for a logical task.
void declare_Gadget(py::module &m)
{
    py::class_<Gadget>(m, "Gadget")
        .def("init", &Gadget::init)
        .def("generateConstraints", &Gadget::generateConstraints)
        .def("generateWitness", &Gadget::generateWitness)
        .def("addUnaryConstraint", &Gadget::addUnaryConstraint)
        .def("addRank1Constraint", &Gadget::addRank1Constraint)
        .def("enforceBooleanity", &Gadget::enforceBooleanity)
        .def("fieldType", &Gadget::fieldType)
        .def("flagIsSet", &Gadget::flagIsSet)
        .def("val", py::overload_cast<const Variable &>(&Gadget::val))
        .def("val", py::overload_cast<const LinearCombination &>(&Gadget::val));
}

void declare_R1P_Gadget(py::module &m)
{
    py::class_<R1P_Gadget, Gadget>(m, "R1P_Gadget")
        .def("addRank1Constraint", &R1P_Gadget::addRank1Constraint);
}

void declare_R1P_AND_Gadget(py::module &m)
{
    py::class_<R1P_AND_Gadget>(m, "R1P_AND_Gadget")
        .def("generateConstraints", &R1P_AND_Gadget::generateConstraints)
        .def("generateWitness", &R1P_AND_Gadget::generateWitness);
}

void declare_R1P_OR_Gadget(py::module &m)
{
    py::class_<R1P_OR_Gadget>(m, "R1P_OR_Gadget")
        .def("generateConstraints", &R1P_OR_Gadget::generateConstraints)
        .def("generateWitness", &R1P_OR_Gadget::generateWitness);
}

void declare_R1P_InnerProduct_Gadget(py::module &m)
{
    py::class_<R1P_InnerProduct_Gadget>(m, "R1P_InnerProduct_Gadget")
        .def("generateConstraints", &R1P_InnerProduct_Gadget::generateConstraints)
        .def("generateWitness", &R1P_InnerProduct_Gadget::generateWitness);
}

void declare_R1P_LooseMUX_GadgetBase(py::module &m)
{
    py::class_<LooseMUX_GadgetBase>(m, "LooseMUX_GadgetBase")
        .def("indicatorVariables", &LooseMUX_GadgetBase::indicatorVariables);
}

void declare_R1P_LooseMUX_Gadget(py::module &m)
{
    py::class_<R1P_LooseMUX_Gadget>(m, "R1P_LooseMUX_Gadget")
        .def("indicatorVariables", &R1P_LooseMUX_Gadget::indicatorVariables)
        .def("generateConstraints", &R1P_LooseMUX_Gadget::generateConstraints)
        .def("generateWitness", &R1P_LooseMUX_Gadget::generateWitness);
}

void declare_R1P_CompressionPacking_Gadget(py::module &m)
{
    py::class_<R1P_CompressionPacking_Gadget>(m, "R1P_CompressionPacking_Gadget")
        .def("generateConstraints", &R1P_CompressionPacking_Gadget::generateConstraints)
        .def("generateWitness", &R1P_CompressionPacking_Gadget::generateWitness);
}

void declare_R1P_IntegerPacking_Gadget(py::module &m)
{
    py::class_<R1P_IntegerPacking_Gadget>(m, "R1P_IntegerPacking_Gadget")
        .def("generateConstraints", &R1P_IntegerPacking_Gadget::generateConstraints)
        .def("generateWitness", &R1P_IntegerPacking_Gadget::generateWitness);
}

void declare_R1P_EqualsConst_Gadget(py::module &m)
{
    py::class_<R1P_EqualsConst_Gadget>(m, "R1P_EqualsConst_Gadget")
        .def("generateConstraints", &R1P_EqualsConst_Gadget::generateConstraints)
        .def("generateWitness", &R1P_EqualsConst_Gadget::generateWitness);
}

void declare_DualWord_Gadget(py::module &m)
{
    py::class_<DualWord_Gadget, Gadget>(m, "DualWord_Gadget")
        .def("generateConstraints", &DualWord_Gadget::generateConstraints)
        .def("generateWitness", &DualWord_Gadget::generateWitness);
}

void declare_DualWordArray_Gadget(py::module &m)
{
    py::class_<DualWordArray_Gadget, Gadget>(m, "DualWordArray_Gadget")
        .def("generateConstraints", &DualWordArray_Gadget::generateConstraints)
        .def("generateWitness", &DualWordArray_Gadget::generateWitness);
}

void declare_Toggle_Gadget(py::module &m)
{
    py::class_<Toggle_Gadget, Gadget>(m, "Toggle_Gadget")
        .def("generateConstraints", &Toggle_Gadget::generateConstraints)
        .def("generateWitness", &Toggle_Gadget::generateWitness);
}

void declare_ConditionalFlag_Gadget(py::module &m)
{
    py::class_<ConditionalFlag_Gadget, Gadget>(m, "ConditionalFlag_Gadget")
        .def("generateConstraints", &ConditionalFlag_Gadget::generateConstraints)
        .def("generateWitness", &ConditionalFlag_Gadget::generateWitness);
}

void declare_LogicImplication_Gadget(py::module &m)
{
    py::class_<LogicImplication_Gadget, Gadget>(m, "LogicImplication_Gadget")
        .def("generateConstraints", &LogicImplication_Gadget::generateConstraints)
        .def("generateWitness", &LogicImplication_Gadget::generateWitness);
}

void declare_R1P_Comparison_Gadget(py::module &m)
{
    py::class_<R1P_Comparison_Gadget, Gadget>(m, "R1P_Comparison_Gadget")
        .def("generateConstraints", &R1P_Comparison_Gadget::generateConstraints)
        .def("generateWitness", &R1P_Comparison_Gadget::generateWitness);
}

void init_gadgetlib2_gadget(py::module &m)
{
    declare_Gadget(m);
    declare_R1P_Gadget(m);
    declare_R1P_AND_Gadget(m);
    declare_R1P_OR_Gadget(m);
    declare_R1P_InnerProduct_Gadget(m);
    declare_R1P_LooseMUX_GadgetBase(m);
    declare_R1P_LooseMUX_Gadget(m);
    declare_R1P_CompressionPacking_Gadget(m);
    declare_R1P_IntegerPacking_Gadget(m);
    declare_R1P_EqualsConst_Gadget(m);
    declare_DualWord_Gadget(m);
    declare_DualWordArray_Gadget(m);
    declare_Toggle_Gadget(m);
    declare_ConditionalFlag_Gadget(m);
    declare_LogicImplication_Gadget(m);
    declare_R1P_Comparison_Gadget(m);
}