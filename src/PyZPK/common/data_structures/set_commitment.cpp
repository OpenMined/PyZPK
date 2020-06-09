#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <libff/common/serialization.hpp>
#include <libsnark/common/data_structures/set_commitment.hpp>

using namespace std;
namespace py = pybind11;
using namespace libsnark;

void init_data_structures_set_commitment(py::module &m)
{
    // Binding for common/data_structures/set_commitment.cpp // set_membership_proof
    py::class_<set_membership_proof>(m, "set_membership_proof")
        .def("size_in_bits", &set_membership_proof::size_in_bits)
        .def(
            "__eq__", [](set_membership_proof const &self, set_membership_proof const &other) { return self == other; }, py::is_operator());

    // Todo
    // std::ostream& operator<<(std::ostream &out, const set_membership_proof &proof)
    // std::istream& operator>>(std::istream &in, set_membership_proof &proof)
}