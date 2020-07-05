import pytest
import pyzpk

def test_bacs():
    new_num_constraints = 101
    pb = pyzpk.protoboard()

    # Test for pb_variable
    res = pyzpk.pb_variable(0)
    res.allocate(pb, "res")

    # Test for pb_variable_array
    A = pyzpk.pb_variable_array()
    B = pyzpk.pb_variable_array()

    A.allocate(pb, new_num_constraints, "A")
    B.allocate(pb, new_num_constraints, "B")
    assert len(A.get_vals(pb)) == 101
    assert len(B.get_vals(pb)) == 101
    assert A != B

    # Test for pb_linear_combination
    lc = pyzpk.linear_combination()
    pb_lc = pyzpk.pb_linear_combination()
    pb_lc.assign(pb,lc)
    pb_lc.evaluate(pb)
    assert pb_lc.is_constant() == True

    # Test for pb_linear_combination_array
    pb_A = pyzpk.pb_linear_combination_array()
    pb_A.evaluate(pb)

def test_disjunction_gadget():

    # Testing disjunction_gadget on all n bit strings
    n = 10
    pb = pyzpk.protoboard()

    inputs = pyzpk.pb_variable_array()
    inputs.allocate(pb, n, "inputs")

    output = pyzpk.pb_variable(0)
    output.allocate(pb, "output")

    d = pyzpk.disjunction_gadget(pb, inputs, output, "d")
    d.generate_r1cs_constraints()

    for w in range(0, 1<<n):
        for j in range(0, n):
            inputs.get_vals(pb)[j] = pyzpk.Fp_model(pyzpk.bigint(1) if w&(1<<j) else pyzpk.bigint(0))

    d.generate_r1cs_witness()
    assert pb.is_satisfied() == True

