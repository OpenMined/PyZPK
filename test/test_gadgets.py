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

def test_tinyram_control_flow():
    
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

    pb.set_val(argval2.packed, pyzpk.Fp_model(pyzpk.bigint(123)))

    argval2.generate_r1cs_witness_from_packed()
    jmp.generate_r1cs_witness()

    assert pb.get_val(result).is_zero() == pyzpk.Fp_model(pyzpk.bigint(123 >> ap.subaddr_len())).is_zero()
    assert pb.is_satisfied() == True
    
def test_tinyram_argument_decoder():
    ap = pyzpk.tinyram_architecture_params(16,16)
    P = pyzpk.tinyram_program

    P.instructions = pyzpk.generate_tinyram_prelude(ap)

    pb = pyzpk.tinyram_protoboard(ap)

    packed_registers = pyzpk.pb_variable(0)
    packed_registers.allocate(pb, "packed_registers")

    arg2_is_imm = pyzpk.pb_variable_array()

    desidx = pyzpk.dual_variable_gadget(pb, ap.reg_arg_width(), "desidx")
    arg1idx = pyzpk.dual_variable_gadget(pb, ap.reg_arg_width(), "arg1idx")
    arg2idx = pyzpk.dual_variable_gadget(pb, ap.reg_arg_width(), "arg2idx")

    packed_desval = pyzpk.pb_variable(0)
    packed_arg1val = pyzpk.pb_variable(0)
    packed_arg2val = pyzpk.pb_variable(0)

    packed_desval.allocate(pb, "packed_desval")
    packed_arg1val.allocate(pb, "packed_arg1val")
    packed_arg2val.allocate(pb, "packed_arg2val")

    pb.set_val(desidx.packed, pyzpk.Fp_model(pyzpk.bigint(2)))
    pb.set_val(arg1idx.packed, pyzpk.Fp_model(pyzpk.bigint(5)))
    pb.set_val(arg2idx.packed, pyzpk.Fp_model(pyzpk.bigint(10)))

    desidx.generate_r1cs_witness_from_packed()
    arg1idx.generate_r1cs_witness_from_packed()
    arg2idx.generate_r1cs_witness_from_packed()

    assert pb.get_val(packed_desval).is_zero() == pyzpk.Fp_model(pyzpk.bigint(1002)).is_zero()
    assert pb.get_val(packed_desval).is_zero() == pyzpk.Fp_model(pyzpk.bigint(1005)).is_zero()
    assert pb.get_val(packed_desval).is_zero() == pyzpk.Fp_model(pyzpk.bigint(1007)).is_zero()
    assert pb.is_satisfied() == True
    
def test_knapsack_gadgets():
    dimension = 1
    input_bits = [1,1,0,0,1,0,1,0,0,1]
    digest_bits = [1,1,1,1,0,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,1,1,1,1,0,0,0,0,1,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,1,0,0,0,1,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,1,0,1,0,1,1,0,0,0,1,1,1,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,0,1,1,0,1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0]

    assert pyzpk.knapsack_dimension.dimension == dimension

    pb = pyzpk.protoboard()

    input_block = pyzpk.block_variable(pb, len(input_bits) , "input_block")
    digest_len = pyzpk.knapsack_CRH_with_bit_out_gadget.get_digest_len()
    output_digest = pyzpk.digest_variable(pb, digest_len, "output_digest")
    input_block.generate_r1cs_witness(input_bits);

    assert pb.is_satisfied() == True
    
def test_sha256_gadgets():
    pb = pyzpk.protoboard()
    left = pyzpk.digest_variable(pb,pyzpk.SHA256_digest_size, "left")
    right = pyzpk.digest_variable(pb,pyzpk.SHA256_digest_size, "right")
    output = pyzpk.digest_variable(pb,pyzpk.SHA256_digest_size, "output")
    f = pyzpk.sha256_two_to_one_hash_gadget(pb, left, right, output, "f")
    f.generate_r1cs_constraints(True)

    # Number of constraints for sha256_two_to_one_hash_gadget
    assert pb.num_constraints() == 27280

    left_bv = [0x426bc2d8, 0x4dc86782, 0x81e8957a, 0x409ec148, 0xe6cffbe8, 0xafe6ba4f, 0x9c6f1978, 0xdd7af7e9]
    right_bv = [0x038cce42, 0xabd366b8, 0x3ede7e00, 0x9130de53, 0x72cdf73d, 0xee825114, 0x8cb48d1b, 0x9af68ad0]
    hash_bv = [0xeffd0b7f, 0x1ccba116, 0x2ee816f7, 0x31c62b48, 0x59305141, 0x990e5c0a, 0xce40d33d, 0x0b1167d1]
    left.generate_r1cs_witness(left_bv)
    right.generate_r1cs_witness(right_bv)
    f.generate_r1cs_witness()
    output.generate_r1cs_witness(hash_bv)
    assert pb.is_satisfied() == True
