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
