#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/operators.h>
#include <libsnark/gadgetlib2/variable.hpp>
#include <vector>

namespace py = pybind11;
using namespace gadgetlib2;

//  Declaration of the low level objects needed for field arithmetization.

// An interface class for field elements.
// Currently 2 classes will derive from this interface:
// R1P_Elem - Elements of a field of prime characteristic
// FConst - Formally not a field, only placeholders for field agnostic constants, such as 0 and 1.
//          Can be used for -1 or any other constant which makes semantic sense in all fields.
void declare_FElemInterface(py::module &m)
{
    py::class_<FElemInterface>(m, "FElemInterface")
        .def("fieldType", &FElemInterface::fieldType)
        .def("asString", &FElemInterface::asString)
        .def("clone", &FElemInterface::clone)
        .def("inverse", &FElemInterface::inverse)
        .def("asLong", &FElemInterface::asLong)
        .def("getBit", &FElemInterface::getBit)
        .def("power", &FElemInterface::power, py::arg("exponent"));
}

// A wrapper class for field elements. Can hold any derived type of FieldElementInterface
void declare_FElem(py::module &m)
{
    py::class_<FElem>(m, "FElem")
        .def("promoteToFieldType", &FElem::promoteToFieldType)
        .def(py::init<>())
        .def(py::init<const FElemInterface &>())
        .def(py::init<const long>())
        .def(py::init<const int>())
        .def(py::init<const size_t>())
        .def(py::init<const Fp &>())
        .def(py::init<const FElem &>())
        .def("asString", &FElem::asString)
        .def("fieldType", &FElem::fieldType)
        .def(bool() == py::self)
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(-py::self)
        .def("inverse", &FElem::inverse)
        .def("asLong", &FElem::asLong)
        .def("getBit", &FElem::getBit, py::arg("i"), py::arg("fieldType"));
}

void declare_FConst(py::module &m)
{
    py::class_<FConst, FElemInterface>(m, "FConst")
        .def("fieldType", &FConst::fieldType)
        .def("asString", &FConst::asString)
        .def("clone", &FConst::clone)
        .def("inverse", &FConst::inverse)
        .def("asLong", &FConst::asLong)
        .def("getBit", &FConst::getBit)
        .def("power", &FConst::power, py::arg("exponent"));
}

void declare_R1P_Elem(py::module &m)
{
    py::class_<R1P_Elem, FElemInterface>(m, "R1P_Elem")
        .def(py::init<const Fp &>())
        .def("fieldType", &R1P_Elem::fieldType)
        .def("asString", &R1P_Elem::asString)
        .def("clone", &R1P_Elem::clone)
        .def("inverse", &R1P_Elem::inverse)
        .def("asLong", &R1P_Elem::asLong)
        .def("getBit", &R1P_Elem::getBit)
        .def("power", &R1P_Elem::power, py::arg("exponent"));
}

void declare_Variable(py::module &m)
{
    py::enum_<FieldType>(m, "FieldType", py::arithmetic())
        .value("R1P", R1P)
        .value("AGNOSTIC", AGNOSTIC);

    py::class_<Variable>(m, "Variable")
        .def(py::init<const ::std::string &>())
        .def("name", &Variable::name)
        .def("eval", &Variable::eval)
        .def(py::self * int())
        .def(int() * py::self);
}

void declare_VariableArray(py::module &m)
{
    typedef ::std::vector<Variable> VariableArrayContents;
    py::class_<VariableArrayContents>(m, "VariableArrayContents");

    py::class_<VariableArray, VariableArrayContents>(m, "VariableArray")
        .def(py::init<const ::std::string &>())
        .def(py::init<const int, const ::std::string &>())
        .def(py::init<const size_t, const ::std::string &>())
        .def(py::init<const size_t, const Variable &>())
        .def("name", &VariableArray::name)
        // .def(
        //     "__getitem__", [](int i) { return VariableArray[i]})
        ;
}

// Holds variables whose purpose is to be populated with the unpacked form of some word, bit by bit
void declare_UnpackedWord(py::module &m)
{
    py::class_<UnpackedWord, VariableArray>(m, "UnpackedWord")
        .def(py::init<>())
        .def(py::init<const size_t, const ::std::string &>())
        .def("name", &UnpackedWord::name);
}

// Holds variables whose purpose is to be populated with the packed form of some word.
// word representation can be larger than a single field element in small enough fields
void declare_MultiPackedWord(py::module &m)
{
    py::class_<MultiPackedWord, VariableArray>(m, "MultiPackedWord")
        .def(py::init<const FieldType &>())
        .def(py::init<const size_t, const FieldType &, const ::std::string &>())
        .def("resize", &MultiPackedWord::resize)
        .def("name", &MultiPackedWord::name);
}

// Holds both representations of a word, both multipacked and unpacked
void declare_DualWord(py::module &m)
{
    py::class_<DualWord>(m, "DualWord")
        .def(py::init<const FieldType &>())
        .def(py::init<const size_t, const FieldType &, const ::std::string &>())
        .def(py::init<const MultiPackedWord &, const UnpackedWord &>())
        .def("multipacked", &DualWord::multipacked)
        .def("unpacked", &DualWord::unpacked)
        .def("bit", &DualWord::bit)
        .def("numBits", &DualWord::numBits)
        .def("resize", &DualWord::resize);
}

void declare_DualWordArray(py::module &m)
{
    py::class_<DualWordArray>(m, "DualWordArray")
        .def(py::init<const FieldType &>())
        .def(py::init<const MultiPackedWordArray &, const UnpackedWordArray &>())
        .def("multipacked", &DualWordArray::multipacked)
        .def("unpacked", &DualWordArray::unpacked)
        .def("packed", &DualWordArray::packed)
        .def("push_back", &DualWordArray::push_back)
        .def("at", &DualWordArray::at)
        .def("size", &DualWordArray::size);
}

void declare_LinearTerm(py::module &m)
{
    py::class_<LinearTerm>(m, "LinearTerm")
        .def(py::init<const Variable &>())
        .def(py::init<const Variable &, const FElem &>())
        .def(py::init<const Variable &, long>())
        .def(-py::self)
        .def(py::self *= FElem())
        .def(py::self + py::self)
        .def(py::self + int())
        .def("fieldtype", &LinearTerm::fieldtype)
        .def("asString", &LinearTerm::asString)
        .def("eval", &LinearTerm::eval, py::arg("VariableAssignment"))
        .def("variable", &LinearTerm::variable);
}

void declare_LinearCombination(py::module &m)
{
    py::class_<LinearCombination>(m, "LinearCombination")
        .def(py::init<>())
        .def(py::init<const Variable &>())
        .def(py::init<const LinearTerm &>())
        .def(py::init<long>())
        .def(py::init<const FElem &>())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= FElem())
        .def(py::self + int())
        .def("eval", &LinearCombination::eval, py::arg("VariableAssignment"))
        .def("asString", &LinearCombination::asString)
        .def("getUsedVariables", &LinearCombination::getUsedVariables);
}

void declare_Monomial(py::module &m)
{
    py::class_<Monomial>(m, "Monomial")
        .def(py::init<const Variable &>())
        .def(py::init<const Variable &, const FElem &>())
        .def(py::init<const FElem &>())
        .def(py::init<const LinearTerm &>())
        .def(-py::self)
        .def(py::self *= py::self)
        .def("getUsedVariables", &Monomial::getUsedVariables)
        .def("asString", &Monomial::asString)
        .def("eval", &Monomial::eval)
        .def("getCoefficient", &Monomial::getCoefficient);
}

void declare_Polynomial(py::module &m)
{
    py::class_<Polynomial>(m, "Polynomial")
        .def(py::init<>())
        .def(py::init<const Monomial &>())
        .def(py::init<const Variable &>())
        .def(py::init<const FElem &>())
        .def(py::init<const LinearCombination &>())
        .def(py::init<const LinearTerm &>())
        .def(py::init<int>())
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def("eval", &Polynomial::eval)
        .def("getUsedVariables", &Polynomial::getUsedVariables)
        .def("getMonomials", &Polynomial::getMonomials)
        .def("getConstant", &Polynomial::getConstant)
        .def("asString", &Polynomial::asString);
}

void init_gadgetlib2_variable(py::module &m)
{
    declare_FElemInterface(m);
    declare_FElem(m);
    declare_FConst(m);
    declare_R1P_Elem(m);
    declare_Variable(m);
    declare_VariableArray(m);
    declare_UnpackedWord(m);
    declare_MultiPackedWord(m);
    declare_DualWord(m);
    declare_DualWordArray(m);
    declare_LinearTerm(m);
    declare_LinearCombination(m);
    declare_Monomial(m);
}