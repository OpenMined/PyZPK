import pyzpk
import torch
import math
import random
RAND_MAX = 32767

# Input bits/digest bits tensor
input_bits_tensor = torch.Tensor([1,1,0,0,1,0,1,0,0,1])
digest_bits_tensor = torch.Tensor([1,1,1,1,0,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,1,1,1,1,0,0,0,0,1,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,1,0,0,0,1,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,1,0,1,0,1,1,0,0,0,1,1,1,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,0,1,1,0,1,1,1,0,0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0])

# Tensor() ---> List()
input_bits = input_bits_tensor.tolist()
digest_bits = digest_bits_tensor.tolist()

dimension = 1
assert pyzpk.knapsack_dimension.dimension == dimension

# Create protoboard
pb = pyzpk.protoboard()
input_block = pyzpk.block_variable(pb, len(input_bits) , "input_block")
digest_len = pyzpk.knapsack_CRH_with_bit_out_gadget.get_digest_len()
output_digest = pyzpk.digest_variable(pb, digest_len, "output_digest")
input_block.generate_r1cs_witness(input_bits);

# Validity of Protoboard
assert pb.is_satisfied() == True 
output = input_block.get_block()
output_tensor = torch.Tensor(output)

# Given a R1CS (Rank-1 constraint system) aka example, it 
# generates a keypair one for the prover and the other for the verifier. 
num_constraints, input_size = 1000, 100
example = pyzpk.generate_r1cs_example_with_binary_input(
    num_constraints, input_size)
assert example.constraint_system.num_variables() == example.constraint_system.num_inputs() + example.constraint_system.num_constraints()

# The inputs include both public values (primary_input, known also to the verifier) and 
# private “witness” values (auxiliary_input, not revealed to the verifier)].
primary_input_size = auxiliary_input_size = 10
num_gates, num_outputs, num_tbcs_gate_types = 20, 5, 16
test_serialization = True
example = pyzpk.tbcs_example()
primary_input_list = list()
auxiliary_input_list = list()
for i in range(0, primary_input_size):
    primary_input_list.append(
        False if random.randint(0, RAND_MAX) % 2 == 0 else True)
for i in range(0, auxiliary_input_size):
    auxiliary_input_list.append(
        False if random.randint(0, RAND_MAX) % 2 == 0 else True)

example.circuit.primary_input_size = primary_input_size #public values
example.circuit.auxiliary_input_size = auxiliary_input_size #private values unknown to verifiers

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

assert isinstance(all_vals, list)

# output in Tensor form
all_vals = torch.Tensor(all_vals)
assert torch.is_tensor(all_vals)

# Together with the public inputs and the verification key, the verifier checks the proof 
# which should return true if the proof was indeed 
# provided a satisfying witness by the prover.
assert example.circuit.is_satisfied(
    primary_input_list, auxiliary_input_list) == True