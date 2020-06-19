import pytest
import pyzpk
import math

# Test for QAP
@pytest.mark.parametrize("qap_degree, num_inputs, binary_input",
                         [
                             # basic_domain_size
                             (1 << pyzpk.mnt6_Fr_s, 10, True),
                             # step_domain_size
                             ((1 << 10) + (1 << 8), 10, True),
                             # extended_domain_size
                             (1 << (pyzpk.mnt6_Fr_s+1), 10, True),
                             # extended_domain_size_special
                             ((1 << (pyzpk.mnt6_Fr_s+1))-1, 10, True)
                         ])
def test_qap(qap_degree, num_inputs, binary_input):
    assert num_inputs + 1 <= qap_degree
    num_constraints = qap_degree - num_inputs - 1
    # For Binary input
    if binary_input:
        example = pyzpk.generate_r1cs_example_with_binary_input(
            num_constraints, num_inputs)

    assert example.constraint_system.is_satisfied(
        example.primary_input, example.auxiliary_input)
    t = pyzpk.Fp_model.random_element()
    d1 = pyzpk.Fp_model.random_element()
    d2 = pyzpk.Fp_model.random_element()
    d3 = pyzpk.Fp_model.random_element()

# Test for SAP
@pytest.mark.parametrize("sap_degree, num_inputs, binary_input",
                         [
                             # basic_domain_size_special
                             ((1 << pyzpk.mnt6_Fr_s) - 1, 10, True),
                             #  # step_domain_size_special
                             ((1 << 10) + (1 << 8) - 1, 10, True),
                             #  # extended_domain_size_special
                             (1 << (pyzpk.mnt6_Fr_s+1) - 1, 10, True)
                         ])
def test_sap(sap_degree, num_inputs, binary_input):
    num_constraints = int((sap_degree - 1) / 2) - num_inputs
    assert num_constraints >= 1
    # For Binary input
    if binary_input:
        example = pyzpk.generate_r1cs_example_with_binary_input(
            num_constraints, num_inputs)
    assert example.constraint_system.is_satisfied(
        example.primary_input, example.auxiliary_input)
    t = pyzpk.Fp_model.random_element()
    d1 = pyzpk.Fp_model.random_element()
    d2 = pyzpk.Fp_model.random_element()
    d3 = pyzpk.Fp_model.random_element()

# Test for SSP
@pytest.mark.parametrize("num_constraints, num_inputs, binary_input",
                         [
                             # basic_domain_size, binary_input
                             (1 << pyzpk.mnt6_Fr_s, 10, True),
                             # step_domain_size, binary_input
                             ((1 << 10) + (1 << 8), 10, True),
                             # extended_domain_size, binary_input
                             (1 << (pyzpk.mnt6_Fr_s+1), 10, True),
                             # extended_domain_size_special, binary_input
                             ((1 << (pyzpk.mnt6_Fr_s+1))-1, 10, True),
                             # basic_domain_size, field_input
                             (1 << pyzpk.mnt6_Fr_s, 10, False),
                             # step_domain_size, field_input
                             ((1 << 10) + (1 << 8), 10, False),
                             # extended_domain_size, field_input
                             (1 << (pyzpk.mnt6_Fr_s+1), 10, False),
                             # extended_domain_size_special, field_input
                             ((1 << (pyzpk.mnt6_Fr_s+1))-1, 10, False)
                         ])
def test_ssp(num_constraints, num_inputs, binary_input):
    # For Binary input
    if binary_input:
        example = pyzpk.generate_uscs_example_with_binary_input(
            num_constraints, num_inputs)
    else:
        example = pyzpk.generate_uscs_example_with_field_input(
            num_constraints, num_inputs)
    assert example.constraint_system.is_satisfied(
        example.primary_input, example.auxiliary_input)
    t = pyzpk.Fp_model.random_element()
    d1 = pyzpk.Fp_model.random_element()