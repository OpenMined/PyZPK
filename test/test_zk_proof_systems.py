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