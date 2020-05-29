#include <pybind11/pybind11.h>
#include <libsnark/common/data_structures/integer_permutation.cpp>
int add(int i, int j)
{
    return i + j;
}
// using namespace std;
using namespace libsnark;
namespace py = pybind11;

PYBIND11_MODULE(pyzpk, m)
{
    m.doc() = "Python wrapper for open source Zero Proof Knowledge Library";

    m.def("add", &add, R"pbdoc(
        Add two numbers
    )pbdoc");
}

