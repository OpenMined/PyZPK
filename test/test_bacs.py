import random
import pytest
import pyzpk
import math

# Test for BACS
# Steps:
# 1. Select primary and auxiliary inputs uniformly at random
# 2. For each gate select random left and right wires from primary inputs, auxiliary inputs, and outputs of previous gates
# 3. Selecting random linear combinations for left and right wires, consisting of 1, 2, 3 or 4 terms each, with random coefficients,
# 4. If the gate is an output gate, then adding a random non-output wire to either left or right linear combination, with appropriate
#    coefficient, so that the linear combination evaluates to 0.


@pytest.mark.parametrize("primary_input_size, auxiliary_input_size, num_gates, num_outputs",
                         [(10, 10, 20, 5)])
def test_bacs(primary_input_size, auxiliary_input_size, num_gates, num_outputs):
    assert num_outputs <= num_gates
    example = pyzpk.bacs_example()
    primary_input_list = list()
    auxiliary_input_list = list()
    for i in range(0, primary_input_size):
        primary_input_list.append(pyzpk.Fp_model.random_element())
    for i in range(0, auxiliary_input_size):
        auxiliary_input_list.append(pyzpk.Fp_model.random_element())

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
            # the linear combination evaluates to 0.
            assert(gate.evaluate(all_vals).is_zero())
        else:
            gate.is_circuit_output = False
        example.circuit.add_gate(gate)
        evl_val = gate.evaluate(all_vals)
        all_vals.append(evl_val)

    assert example.circuit.is_satisfied(
        primary_input_list, auxiliary_input_list)
