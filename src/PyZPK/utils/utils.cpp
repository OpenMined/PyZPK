#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/cast.h>
#include <pybind11/complex.h>
#include <pybind11/operators.h>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>
#include <cstddef>
#include <iostream>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_g1.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_g2.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pairing.hpp>
#include <libff/algebra/curves/public_params.hpp>
#include <libff/algebra/exponentiation/exponentiation.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/fields/bigint.hpp>
#include <libff/algebra/fields/fp_aux.tcc>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libff/common/serialization.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_g2.hpp>
#include <libff/algebra/curves/mnt/mnt4/mnt4_g1.hpp>
#include <libff/algebra/curves/mnt/mnt4/mnt4_g2.hpp>
#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <libff/algebra/curves/alt_bn128/alt_bn128_init.hpp>
#include <gmp.h>

using namespace std;
namespace py = pybind11;
using namespace libff;

// Used as FieldT class type
void declare_utils_Fp_model(py::module &m)
{
    // bigint wrapper class around GMP's MPZ long integers.
    py::class_<bigint<5l>>(m, "bigint")
        .def(py::init<>())
        .def(py::init<const unsigned long>())
        .def(py::init<const char *>())
        .def("test_bit", &bigint<5l>::test_bit)
        .def("randomize", &bigint<5l>::randomize);

    //  Implementation of arithmetic in the finite field F[p], for prime p of fixed length.
    py::class_<Fp_model<5l, libff::mnt46_modulus_B>>(m, "Fp_model")
        .def(py::init<>())
        .def(py::init<const bigint<5l> &>())
        .def(py::init<const long, const bool>())
        .def_readwrite("mont_repr", &Fp_model<5l, libff::mnt46_modulus_B>::mont_repr)
        .def_static("random_element", []() {
            Fp_model<5l, mnt46_modulus_B> r;
            while (mpn_cmp(r.mont_repr.data, mnt46_modulus_B.data, 5l))
            {
                r.mont_repr.randomize();
                size_t bitno = GMP_NUMB_BITS * 5 - 1;
                while (mnt46_modulus_B.test_bit(bitno) == false)
                {
                    const size_t part = bitno / GMP_NUMB_BITS;
                    const size_t bit = bitno - (GMP_NUMB_BITS * part);
                    r.mont_repr.data[part] &= ~(1ul << bit);
                    bitno--;
                }
            }
            return r;
        })
        .def("inverse", &Fp_model<5l, libff::mnt46_modulus_B>::inverse)
        .def("print", &Fp_model<5l, libff::mnt46_modulus_B>::print)
        .def("is_zero", &Fp_model<5l, libff::mnt46_modulus_B>::is_zero)
        .def_static("one", &Fp_model<5l, libff::mnt46_modulus_B>::one)
        .def_static("zero", &Fp_model<5l, libff::mnt46_modulus_B>::zero)
        .def_static("size_in_bits", &Fp_model<5l, libff::mnt46_modulus_B>::size_in_bits)
        .def("as_ulong", &Fp_model<5l, libff::mnt46_modulus_B>::as_ulong)
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(-py::self);


        py::class_<Fp_model<4l, libff::alt_bn128_modulus_r>>(m, "Fp_model4bn")
        .def(py::init<>())
        .def(py::init<const bigint<4l> &>())
        .def(py::init<const long, const bool>())
        .def_readwrite("mont_repr", &Fp_model<4l, libff::alt_bn128_modulus_r>::mont_repr)
        .def_static("random_element", []() {
            Fp_model<5l, mnt46_modulus_B> r;
            while (mpn_cmp(r.mont_repr.data, mnt46_modulus_B.data, 5l))
            {
                r.mont_repr.randomize();
                size_t bitno = GMP_NUMB_BITS * 5 - 1;
                while (mnt46_modulus_B.test_bit(bitno) == false)
                {
                    const size_t part = bitno / GMP_NUMB_BITS;
                    const size_t bit = bitno - (GMP_NUMB_BITS * part);
                    r.mont_repr.data[part] &= ~(1ul << bit);
                    bitno--;
                }
            }
            return r;
        })
        .def("inverse", &Fp_model<4l, libff::alt_bn128_modulus_r>::inverse)
        .def("print", &Fp_model<4l, libff::alt_bn128_modulus_r>::print)
        .def("is_zero", &Fp_model<4l, libff::alt_bn128_modulus_r>::is_zero)
        .def_static("one", &Fp_model<4l, libff::alt_bn128_modulus_r>::one)
        .def_static("zero", &Fp_model<4l, libff::alt_bn128_modulus_r>::zero)
        .def_static("size_in_bits", &Fp_model<4l, libff::alt_bn128_modulus_r>::size_in_bits)
        .def("as_ulong", &Fp_model<4l, libff::alt_bn128_modulus_r>::as_ulong)
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(-py::self);
}

void declare_G1(py::module &m)
{
    py::class_<mnt4_G1>(m, "mnt4_G1")
        .def(py::init<>())
        .def_static("one", &mnt4_G1::one);
}

void declare_G2(py::module &m)
{
    py::class_<mnt4_G2>(m, "mnt4_G2")
        .def(py::init<>())
        .def_static("one", &mnt4_G2::one);
}

void init_utils(py::module &m)
{
    declare_utils_Fp_model(m);
    declare_G1(m);
    declare_G2(m);
}