#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>

#include <libsnark/gadgetlib1/gadgets/routing/profiling/profile_routing_gadgets.cpp>

namespace py = pybind11;
using namespace libsnark;
using namespace libff;

//  Functions to profile the gadgetlib1 implementations of Benes and AS-Waksman routing networks.
void init_gadgetlib1_routing_profile_routing_gadgets(py::module &m)
{
    using FieldT = Fp_model<5l, libff::mnt46_modulus_B>;

    m.def("get_as_waksman_size", &get_as_waksman_size<FieldT>);
    m.def("get_benes_size", &get_benes_size<FieldT>);
    m.def("profile_routing_gadgets", &profile_routing_gadgets<FieldT>);
    m.def("profile_num_switches", &profile_num_switches<FieldT>);
}