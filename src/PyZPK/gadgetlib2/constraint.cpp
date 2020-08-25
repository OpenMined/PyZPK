#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <libsnark/gadgetlib2/constraint.hpp>

namespace py = pybind11;
using namespace gadgetlib2;

//  Declaration of the Constraint class.
//  A constraint is an algebraic equation which can be either satisfied by an assignment,
//  (the equation is true with that assignment) or unsatisfied. For instance the rank-1
//  constraint (X * Y = 15) is satisfied by {X=5 Y=3} or {X=3 Y=5}
void declare_Constraint(py::module &m)
{
    py::class_<Constraint>(m, "Constraint")
        .def("name", &Constraint::name)
        .def("isSatisfied", &Constraint::isSatisfied, py::arg("assignment"), py::arg("printOnFail"))
        .def("annotation", &Constraint::annotation)
        .def("getUsedVariables", &Constraint::getUsedVariables)
        .def("asPolynomial", &Constraint::asPolynomial);
}

// A rank-1 prime characteristic constraint. The constraint is defined by <a,x> * <b,x> = <c,x>
// where x is an assignment of field elements to the variables.
void declare_Rank1Constraint(py::module &m)
{
    py::class_<Rank1Constraint, Constraint>(m, "Rank1Constraint")
        .def(py::init<const LinearCombination &,
                      const LinearCombination &,
                      const LinearCombination &,
                      const ::std::string &>())
        .def("a", &Rank1Constraint::a)
        .def("b", &Rank1Constraint::b)
        .def("c", &Rank1Constraint::c)
        .def("isSatisfied", &Rank1Constraint::isSatisfied, py::arg("assignment"), py::arg("printOnFail"))
        .def("annotation", &Rank1Constraint::annotation)
        .def("getUsedVariables", &Rank1Constraint::getUsedVariables)
        .def("asPolynomial", &Rank1Constraint::asPolynomial);
}

void declare_PolynomialConstraint(py::module &m)
{
    py::class_<PolynomialConstraint, Constraint>(m, "PolynomialConstraint")
        .def(py::init<const Polynomial &,
                      const Polynomial &,
                      const ::std::string &>())
        .def("isSatisfied", &PolynomialConstraint::isSatisfied, py::arg("assignment"), py::arg("printOnFail"))
        .def("annotation", &PolynomialConstraint::annotation)
        .def("getUsedVariables", &PolynomialConstraint::getUsedVariables)
        .def("asPolynomial", &PolynomialConstraint::asPolynomial);
}

void declare_ConstraintSystem(py::module &m)
{
    py::class_<ConstraintSystem>(m, "ConstraintSystem")
        .def(py::init<>())
        .def("isSatisfied", &ConstraintSystem::isSatisfied, py::arg("assignment"), py::arg("printOnFail"))
        .def("annotation", &ConstraintSystem::annotation)
        .def("getUsedVariables", &ConstraintSystem::getUsedVariables)
        .def("getNumberOfConstraints", &ConstraintSystem::getNumberOfConstraints)
        .def("getConstraint", &ConstraintSystem::getConstraint, py::arg("idx"))
        .def("addConstraint", py::overload_cast<const Rank1Constraint &>(&ConstraintSystem::addConstraint), py::arg("Rank1Constraint"))
        .def("addConstraint", py::overload_cast<const PolynomialConstraint &>(&ConstraintSystem::addConstraint), py::arg("PolynomialConstraint"));
}

void init_gadgetlib2_constraint(py::module &m)
{
    declare_Constraint(m);
    declare_Rank1Constraint(m);
    declare_PolynomialConstraint(m);
    declare_ConstraintSystem(m);
}