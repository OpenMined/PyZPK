import random
import pytest
import pyzpk
import math
RAND_MAX = 32767

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

def test_merkle_tree():
    digest_len = 298
    tree_depth = 16
    prev_path = []
    prev_load_hash = []
    prev_store_hash = []
    for i in range(digest_len):
        prev_load_hash.append(random.randint(0, RAND_MAX) % 2)
        prev_store_hash.append(random.randint(0, RAND_MAX) % 2)
    for i in range(tree_depth):
        prev_path.append(random.randint(0, RAND_MAX) % 2)

    address = 0
    address_bits = []
    while tree_depth > 0:
        level = tree_depth - 1
        computed_is_right = random.randint(0, RAND_MAX) % 2

        address |= 1 << (tree_depth-1-level) if computed_is_right == 1 else 0
        address_bits.append(computed_is_right)
        other = []
        for i in range(digest_len):
            other.append(random.randint(0, RAND_MAX) % 2)

        prev_path[level] = other

        tree_depth -= 1

    tree_depth = 16
    pb = pyzpk.protoboard()
    address_bits_va = pyzpk.pb_variable_array()
    address_bits_va.allocate(pb, tree_depth, "address_bits")

    prev_leaf_digest = pyzpk.digest_variable(pb, digest_len, "prev_leaf_digest")
    prev_root_digest = pyzpk.digest_variable(pb, digest_len, "prev_root_digest")
    prev_path_var = pyzpk.merkle_authentication_path_variable(
        pb, tree_depth, "prev_path_var")

    next_leaf_digest = pyzpk.digest_variable(pb, digest_len, "next_leaf_digest")
    next_root_digest = pyzpk.digest_variable(pb, digest_len, "next_root_digest")
    next_path_var = pyzpk.merkle_authentication_path_variable(
        pb, tree_depth, "next_path_var")

    prev_path_var.generate_r1cs_constraints()
    address_bits_va.fill_with_bits(pb, address_bits)
    assert address_bits_va.get_field_element_from_bits(pb).as_ulong() == 0
    prev_leaf_digest.generate_r1cs_witness(prev_load_hash)
    next_leaf_digest.generate_r1cs_witness(prev_store_hash)
    address_bits_va.fill_with_bits(pb, address_bits)

    prev_leaf_digest.generate_r1cs_witness(prev_load_hash)
    next_leaf_digest.generate_r1cs_witness(prev_store_hash)
    prev_root_digest.generate_r1cs_witness(prev_load_hash)
    next_root_digest.generate_r1cs_witness(prev_store_hash)
    address_bits_va.fill_with_bits(pb, address_bits)
    assert pb.is_satisfied() == True

def test_mnt_miller_loop():
    pb = pyzpk.protoboard()
    P_val = pyzpk.mnt4_G1.one()
    Q_val = pyzpk.mnt4_G2.one()

    P = pyzpk.G1_variable(pb, "P")
    Q = pyzpk.G2_variable(pb, "Q")
    prec_P = pyzpk.G1_precomputation()
    prec_Q = pyzpk.G2_precomputation()
    compute_prec_P = pyzpk.precompute_G1_gadget(pb, P, prec_P, "prec_P")
    compute_prec_Q = pyzpk.precompute_G2_gadget(pb, Q, prec_Q, "prec_Q")
    compute_prec_P.generate_r1cs_constraints()
    compute_prec_Q.generate_r1cs_constraints()

    P.generate_r1cs_witness(P_val)
    compute_prec_P.generate_r1cs_witness()
    Q.generate_r1cs_witness(Q_val)
    compute_prec_Q.generate_r1cs_witness()
    assert pb.is_satisfied() == True
    
def test_mnt_e_over_e_miller_loop():
    pb = pyzpk.protoboard()
    P1_val = pyzpk.mnt4_G1.one()
    Q1_val = pyzpk.mnt4_G2.one()
    P2_val = pyzpk.mnt4_G1.one()
    Q2_val = pyzpk.mnt4_G2.one()

    P1 = pyzpk.G1_variable(pb, "P1")
    Q1 = pyzpk.G2_variable(pb, "Q1")
    P2 = pyzpk.G1_variable(pb, "P2")
    Q2 = pyzpk.G2_variable(pb, "Q2")

    prec_P1 = pyzpk.G1_precomputation()
    prec_Q1 = pyzpk.G2_precomputation()
    prec_P2 = pyzpk.G1_precomputation()
    prec_Q2 = pyzpk.G2_precomputation()

    compute_prec_P1 = pyzpk.precompute_G1_gadget(pb, P1, prec_P1, "prec_P1")
    compute_prec_Q1 = pyzpk.precompute_G2_gadget(pb, Q1, prec_Q1, "prec_Q1")
    compute_prec_P2 = pyzpk.precompute_G1_gadget(pb, P2, prec_P2, "prec_P2")
    compute_prec_Q2 = pyzpk.precompute_G2_gadget(pb, Q2, prec_Q2, "prec_Q2")
    
    compute_prec_P1.generate_r1cs_constraints()
    compute_prec_Q1.generate_r1cs_constraints()
    compute_prec_P2.generate_r1cs_constraints()
    compute_prec_Q2.generate_r1cs_constraints()

    P1.generate_r1cs_witness(P1_val)
    compute_prec_P1.generate_r1cs_witness()
    Q1.generate_r1cs_witness(Q1_val)
    compute_prec_Q1.generate_r1cs_witness()    
    P2.generate_r1cs_witness(P2_val)
    compute_prec_P2.generate_r1cs_witness()
    Q2.generate_r1cs_witness(Q2_val)
    compute_prec_Q2.generate_r1cs_witness()
    
    assert pb.is_satisfied() == True
    
def test_G1_variable_precomp():
    pb = pyzpk.protoboard()
    g_val = pyzpk.mnt4_G1.one()
    g = pyzpk.G1_variable(pb, "g")
    precomp = pyzpk.G1_precomputation()
    do_precomp = pyzpk.precompute_G1_gadget(pb, g, precomp, "do_precomp")
    do_precomp.generate_r1cs_constraints()
    g.generate_r1cs_witness(g_val)
    do_precomp.generate_r1cs_witness()
    assert pb.is_satisfied() == True
    
def test_routing_gadgets():
    pyzpk.profile_num_switches(1)
    ## Prints out profiling number of switches in arbitrary size networks (and rounded-up for Benes)
    