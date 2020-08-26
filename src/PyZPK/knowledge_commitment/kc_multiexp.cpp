#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libsnark/knowledge_commitment/kc_multiexp.hpp>
#include <libsnark/knowledge_commitment/kc_multiexp.tcc>
namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//   Split out from multiexp to prevent cyclical dependencies. I.e. previously multiexp dependend on
//   knowledge_commitment, which dependend on sparse_vector, which depended on multiexp (to do accumulate).
//   Will probably go away in more general exp refactoring.

void init_knowledge_commitment_kc_multiexp(py::module &m)
{
    using ppT = mnt6_pp;
    using FieldT = Fr<ppT>;
    using T1 = libff::G1<ppT>;
    using T2 = libff::G1<ppT>;

    m.def("opt_window_wnaf_exp", &opt_window_wnaf_exp<T1, T2, 5l>, py::arg("knowledge_commitment_base"), py::arg("scalar"), py::arg("scalar_bit"));
    m.def("kc_multi_exp_with_mixed_addition", &kc_multi_exp_with_mixed_addition<T1, T2, FieldT, libff::multi_exp_method_bos_coster>, py::arg("knowledge_commitment_vector"), 
    py::arg("min_idx"), py::arg("max_idx"), py::arg("scalar_start"), py::arg("scalar_end"), py::arg("chunks"));
    m.def("kc_batch_exp", &kc_batch_exp<T1, T2, FieldT>, py::arg("scalar_size"), py::arg("T1_window"), py::arg("T2_window"), py::arg("T1_table")
    , py::arg("T2_table"), py::arg("T1_coeff"), py::arg("T2_coeff"), py::arg("vector"), py::arg("suggested_num_chunks"));
    m.def("kc_batch_exp_internal", &kc_batch_exp_internal<T1, T2, FieldT>);
}
