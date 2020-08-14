import random
import pyzpk
import math
RAND_MAX = 32767


def test_compliance_predicate():
    type_1 = 1
    type_2 = 2
    max_arity = 2
    wordsize = 32
    relies_on_same_type_inputs = False
    tally_1_accepted_types = {1}
    tally_2_accepted_types = {2, 1}
    tally_1 = pyzpk.tally_cp_handler(
        type_1, max_arity, wordsize, relies_on_same_type_inputs, tally_1_accepted_types)
    tally_2 = pyzpk.tally_cp_handler(
        type_2, max_arity, wordsize, relies_on_same_type_inputs, tally_2_accepted_types)
    tally_1.generate_r1cs_constraints()
    tally_2.generate_r1cs_constraints()
    cp_1 = tally_1.get_compliance_predicate()
    cp_2 = tally_2.get_compliance_predicate()
    assert cp_1 and cp_2


def test_r1cs_mp_ppzkpcd():
    max_arity = 2
    depth = 2  # max_layer
    wordsize = 32
    test_serialization = True
    test_multi_type = True
    test_same_type_optimization = False
    all_accept = True
    tree_size = 0
    nodes_in_layer = 1
    for layer in range(depth+2):
        tree_size = tree_size + nodes_in_layer
        nodes_in_layer = nodes_in_layer*max_arity

    tree_types = []
    tree_elems = []
    tree_arity = []
    for i in range(tree_size):
        tree_arity.append(0)
        tree_elems.append(0)
        tree_types.append(0)

    nodes_in_layer = 1
    node_idx = 0
    for layer in range(0, depth+1):
        for id_in_layer in range(0, nodes_in_layer+1):
            if(not test_multi_type):
                print(node_idx)
                tree_types[node_idx] = 1
            else:
                if(test_same_type_optimization):
                    tree_types[node_idx] = 1 + ((depth-layer) & 1)
                    print(node_idx)
                else:
                    tree_types[node_idx] = 1 + random.randint(0, RAND_MAX) % 2
            tree_elems[node_idx] = random.randint(0, RAND_MAX) % 100
            tree_arity[node_idx] = 1 + \
                (random.randint(0, RAND_MAX) % max_arity)
            node_idx = node_idx + 1
        nodes_in_layer = nodes_in_layer * max_arity

    tree_proofs = []
    tree_messages = []
    for i in range(tree_size):
        tree_proofs.append(0)
        tree_messages.append(0)

    tally_1_accepted_types = {1, 2}
    tally_2_accepted_types = {1}
    tally_1 = pyzpk.tally_cp_handler(
        1, max_arity, wordsize, test_same_type_optimization, tally_1_accepted_types)
    tally_2 = pyzpk.tally_cp_handler(
        2, max_arity, wordsize, test_same_type_optimization, tally_2_accepted_types)
    tally_1.generate_r1cs_constraints()
    tally_2.generate_r1cs_constraints()
    cp_1 = tally_1.get_compliance_predicate()
    cp_2 = tally_2.get_compliance_predicate()

    nodes_in_layer = nodes_in_layer//max_arity
    layer = depth
    while layer >= 0:
        for i in range(0, nodes_in_layer+1):
            cur_idx = (nodes_in_layer - 1) // (max_arity - 1) + i
            cur_tally = tally_1 if tree_types[cur_idx] == 1 else tally_2
            cur_cp = cp_1 if tree_types[cur_idx] == 1 else cp_2
            base_case = (max_arity * cur_idx + max_arity >= tree_size)
            proofs = []
            if not base_case:
                for i in range(0, max_arity):
                    proofs.append(tree_proofs[max_arity*cur_idx + i + 1])
        layer = layer - 1
        nodes_in_layer = nodes_in_layer//max_arity


def test_r1cs_sp_ppzkpcd():
    max_arity = 2
    depth = 2  # max_layer
    wordsize = 32
    test_serialization = True
    all_accept = True
    tree_size = 0
    nodes_in_layer = 1
    for layer in range(depth+2):
        tree_size = tree_size + nodes_in_layer
        nodes_in_layer = nodes_in_layer*max_arity

    tree_elems = []
    for i in range(tree_size + 1):
        tree_elems.append(0)
    for i in range(0, tree_size+1):
        tree_elems[i] = random.randint(0, RAND_MAX) % 10

    tree_proofs = []
    tree_messages = []
    for i in range(tree_size):
        tree_proofs.append(0)
        tree_messages.append(0)

    type = 1
    tally_accepted_types = {1, 2}
    test_same_type_optimization = True
    tally = pyzpk.tally_cp_handler(
        type, max_arity, wordsize, test_same_type_optimization, tally_accepted_types)
    tally.generate_r1cs_constraints()
    tally_cp = tally.get_compliance_predicate()
    nodes_in_layer = nodes_in_layer//max_arity


def test_r1cs_ppzkadsnark():
    test_serialization = True
    auth_keys = pyzpk.r1cs_ppzkadsnark_auth_keys()
    keypair = pyzpk.r1cs_ppzkadsnark_auth_keys()
    pvk = pyzpk.r1cs_ppzkadsnark_processed_verification_key()
    labels = []
    for i in range(10):
        labels.append(pyzpk.labelT())


def test_se_and_gg_ppzksnark():
    num_constraints = 1000
    input_size = 100
    test_serialization = True
    example = pyzpk.generate_r1cs_example_with_binary_input(
        num_constraints, input_size)
    assert(example)


def test_bacs_ppzksnark():
    primary_input_size = 10
    auxiliary_input_size = 10
    num_gates = 20
    num_outputs = 5
    test_serialization = True
    example = pyzpk.bacs_example()
    primary_input_list = list()
    auxiliary_input_list = list()
    for i in range(0, primary_input_size):
        primary_input_list.append(pyzpk.Fp_model4bn.random_element())
    for i in range(0, auxiliary_input_size):
        auxiliary_input_list.append(pyzpk.Fp_model4bn.random_element())

    example.circuit.primary_input_size = primary_input_size
    example.circuit.auxiliary_input_size = auxiliary_input_size

    all_vals = list()
    all_vals.extend(primary_input_list)
    all_vals.extend(auxiliary_input_list)
    all_vals.extend(all_vals)
    for i in range(0, num_gates):
        num_variables = primary_input_size + auxiliary_input_size + i
        gate = pyzpk.bacs_gate()
        gate.lhs = pyzpk.random_linear_combination(num_variables)
        gate.rhs = pyzpk.random_linear_combination(num_variables)
        gate.output = pyzpk.variable(num_variables+1)
        if(i >= num_gates - num_outputs):
            gate.is_circuit_output = True
            var_idx = random.randint(
                0, (primary_input_size + auxiliary_input_size))
            var_val = pyzpk.Fp_model.one(
            ) if var_idx == 0 else all_vals[var_idx-1]
            if random.randint(0, (primary_input_size + auxiliary_input_size)) % 2 == 0:
                lhs_val = gate.lhs.evaluate(all_vals)
                coeff = -(lhs_val * var_val.inverse())
                gate.lhs = gate.lhs + coeff * pyzpk.variable(var_idx)
            else:
                rhs_val = gate.rhs.evaluate(all_vals)
                coeff = -(rhs_val * var_val.inverse())
                gate.rhs = gate.rhs + coeff * pyzpk.variable(var_idx)
            assert(gate.evaluate(all_vals).is_zero())
        else:
            gate.is_circuit_output = False
        example.circuit.add_gate(gate)
        evl_val = gate.evaluate(all_vals)
        all_vals.append(evl_val)

    assert example.circuit.is_satisfied(
        primary_input_list, auxiliary_input_list)

def test_uscs_ppzksnark():
    num_constraints = 1000
    input_size = 100
    test_serialization = True
    example = pyzpk.generate_uscs_example_with_binary_input(
        num_constraints, input_size)
    assert(example)

def test_ram_ppzksnark():
    w = 16
    k = 16
    program_size = 16
    input_size = 2
    time_bound = 20
    boot_trace_size_bound = program_size + input_size
    satisfiable = True
    program_size = boot_trace_size_bound / 2
    input_size = boot_trace_size_bound - program_size

    assert 2*w/8*program_size < 1<<(w-1)
    assert w/8*input_size < 1<<(w-1)
    assert input_size >= 1
