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
    tally_1 = pyzpk.tally_cp_handler(type_1, max_arity, wordsize, relies_on_same_type_inputs, tally_1_accepted_types)
    tally_2 = pyzpk.tally_cp_handler(type_2, max_arity, wordsize, relies_on_same_type_inputs, tally_2_accepted_types)
    tally_1.generate_r1cs_constraints()
    tally_2.generate_r1cs_constraints()
    cp_1 = tally_1.get_compliance_predicate()
    cp_2 = tally_2.get_compliance_predicate()
    assert cp_1 and cp_2

def test_r1cs_mp_ppzkpcd():
    max_arity = 2
    depth = 2 #max_layer
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
            tree_arity[node_idx] = 1 + (random.randint(0, RAND_MAX) % max_arity)
            node_idx = node_idx + 1
        nodes_in_layer = nodes_in_layer * max_arity
        
    tree_proofs = []
    tree_messages = []
    for i in range(tree_size):
        tree_proofs.append(0)
        tree_messages.append(0)

    tally_1_accepted_types = {1,2}
    tally_2_accepted_types = {1}
    tally_1 = pyzpk.tally_cp_handler(1, max_arity, wordsize, test_same_type_optimization, tally_1_accepted_types)
    tally_2 = pyzpk.tally_cp_handler(2, max_arity, wordsize, test_same_type_optimization, tally_2_accepted_types)
    tally_1.generate_r1cs_constraints()
    tally_2.generate_r1cs_constraints()
    cp_1 = tally_1.get_compliance_predicate()
    cp_2 = tally_2.get_compliance_predicate()

    nodes_in_layer =  nodes_in_layer//max_arity
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
    depth = 2 #max_layer
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
    tally_accepted_types = {1,2}
    test_same_type_optimization = True
    tally = pyzpk.tally_cp_handler(type, max_arity, wordsize, test_same_type_optimization, tally_accepted_types)
    tally.generate_r1cs_constraints()
    tally_cp = tally.get_compliance_predicate()
    nodes_in_layer =  nodes_in_layer//max_arity