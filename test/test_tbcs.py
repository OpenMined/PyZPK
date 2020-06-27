import random
import pytest
import pyzpk
import math


def test_tbcs_gate_type_enum():
    assert pyzpk.tbcs_gate_type.TBCS_GATE_CONSTANT_0 == 0
    assert pyzpk.tbcs_gate_type.TBCS_GATE_AND == 1
    assert pyzpk.tbcs_gate_type.TBCS_GATE_X_AND_NOT_Y == 2
    assert pyzpk.tbcs_gate_type.TBCS_GATE_X == 3
    assert pyzpk.tbcs_gate_type.TBCS_GATE_NOT_X_AND_Y == 4
    assert pyzpk.tbcs_gate_type.TBCS_GATE_Y == 5
    assert pyzpk.tbcs_gate_type.TBCS_GATE_XOR == 6
    assert pyzpk.tbcs_gate_type.TBCS_GATE_OR == 7
    assert pyzpk.tbcs_gate_type.TBCS_GATE_NOR == 8
    assert pyzpk.tbcs_gate_type.TBCS_GATE_EQUIVALENCE == 9
    assert pyzpk.tbcs_gate_type.TBCS_GATE_NOT_Y == 10
    assert pyzpk.tbcs_gate_type.TBCS_GATE_IF_Y_THEN_X == 11
    assert pyzpk.tbcs_gate_type.TBCS_GATE_NOT_X == 12
    assert pyzpk.tbcs_gate_type.TBCS_GATE_IF_X_THEN_Y == 13
    assert pyzpk.tbcs_gate_type.TBCS_GATE_NAND == 14
    assert pyzpk.tbcs_gate_type.TBCS_GATE_CONSTANT_1 == 15

# Test for TBCS
# Steps:
# 1. First we have to select primary and auxiliary inputs uniformly at random
# 2. For each gate selecting random left and right wires from primary inputs, auxiliary inputs,
# and outputs of previous gates selecting a gate type at random
# 3. subject to the constraint "output = 0" if this is an output gate.


@pytest.mark.parametrize("primary_input_size, auxiliary_input_size, num_gates, num_outputs",
                         [(10, 10, 20, 5)])
def test_tbcs(primary_input_size, auxiliary_input_size, num_gates, num_outputs):
    assert num_outputs <= num_gates
    RAND_MAX = 32767
    num_tbcs_gate_types = 16
    example = pyzpk.tbcs_example()
    primary_input_list = list()
    auxiliary_input_list = list()
    for i in range(0, primary_input_size):
        primary_input_list.append(
            False if random.randint(0, RAND_MAX) % 2 == 0 else True)
    for i in range(0, auxiliary_input_size):
        auxiliary_input_list.append(
            False if random.randint(0, RAND_MAX) % 2 == 0 else True)

    example.circuit.primary_input_size = primary_input_size
    example.circuit.auxiliary_input_size = auxiliary_input_size

    all_vals = list()
    all_vals.extend(primary_input_list)
    all_vals.extend(auxiliary_input_list)
    for i in range(0, num_gates):
        num_variables = primary_input_size + auxiliary_input_size + i
        gate = pyzpk.tbcs_gate()
        gate.left_wire = random.randint(0, RAND_MAX) % (num_variables+1)
        gate.right_wire = random.randint(0, RAND_MAX) % (num_variables+1)
        gate.output = num_variables+1
        if(i >= num_gates - num_outputs):
            while gate.evaluate(all_vals):
                gate.type = (pyzpk.tbcs_gate_type)(
                    random.randint(0, RAND_MAX) % num_tbcs_gate_types)
            gate.is_circuit_output = True
        else:
            gate.type = (pyzpk.tbcs_gate_type)(
                random.randint(0, RAND_MAX) % num_tbcs_gate_types)
            gate.is_circuit_output = False
        example.circuit.add_gate(gate)
        all_vals.append(gate.evaluate(all_vals))

    assert example.circuit.is_satisfied(
        primary_input_list, auxiliary_input_list)
