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
    assert pb_A.evaluate(pb) == None

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

    assert d.generate_r1cs_witness() == None
    assert pb.is_satisfied() == True

def test_conjunction_gadget():

    n = 10
    pb = pyzpk.protoboard()

    inputs = pyzpk.pb_variable_array()
    inputs.allocate(pb, n, "inputs")

    output = pyzpk.pb_variable(0)
    output.allocate(pb, "output")

    c = pyzpk.conjunction_gadget(pb, inputs, output, "c")
    c.generate_r1cs_constraints()

    for w in range(0, 1<<n):
        for j in range(0, n):
            inputs.get_vals(pb)[j] = pyzpk.Fp_model(pyzpk.bigint(1) if w&(1<<j) else pyzpk.bigint(0))

    assert c.generate_r1cs_witness() == None
    assert pb.is_satisfied() == True

def test_comparison_gadget():

    n = 10
    pb = pyzpk.protoboard()

    A = pyzpk.pb_linear_combination()
    B = pyzpk.pb_linear_combination()
    less = pyzpk.pb_variable(0)
    less_or_eq = pyzpk.pb_variable(0)
    lc = pyzpk.linear_combination()

    A.assign(pb, lc) 
    B.assign(pb, lc)

    assert A.evaluate(pb) == None
    assert B.evaluate(pb) == None

    less.allocate(pb, "less")
    less_or_eq.allocate(pb, "less_or_eq")

    cmp = pyzpk.comparison_gadget(pb, n, A, B, less, less_or_eq, "cmp")
    cmp.generate_r1cs_constraints()
    assert cmp.generate_r1cs_witness() == None
    assert pb.is_satisfied() == True

def test_tinyram():
    ap = pyzpk.tinyram_architecture_params(16,16)
    P = pyzpk.tinyram_program
    P.instructions = pyzpk.generate_tinyram_prelude(ap)
    size = len(P.instructions)
    pb = pyzpk.tinyram_protoboard(ap)
    pc = pyzpk.word_variable_gadget(pb, "pc")
    argval2 = pyzpk.word_variable_gadget(pb, "argval2")
    flag = pyzpk.pb_variable(0)
    result = pyzpk.pb_variable(0)
    flag.allocate(pb, "flag")
    result.allocate(pb, "result")
    pc.generate_r1cs_constraints(True)
    argval2.generate_r1cs_constraints(True)
    flag.allocate(pb, "flag")
    result.allocate(pb, "result")
    jmp = pyzpk.ALU_jmp_gadget(pb, pc, argval2, flag, result, "jmp")
    jmp.generate_r1cs_constraints()
    argval2.generate_r1cs_witness_from_packed()
    jmp.generate_r1cs_witness()
    assert pb.is_satisfied() == True