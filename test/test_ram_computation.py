import random
import pytest
import pyzpk
import math
RAND_MAX = 32767

# simple test cases.
# 1. Insert some random address and values in the memory
# 2. Test whether the new insertion is not affecting already existing values.


def test_memory():
    memory_trace = pyzpk.memory_store_trace()
    ra_memory = pyzpk.ra_memory(10, 10)
    timestamp = 0
    address = 4001
    value = 0
    while(timestamp < 10):
        memory_trace.set_trace_entry(timestamp, (address, value))
        ra_memory.set_value(address, value)
        timestamp += 1
        address += 8
        value += 100

    timestamp = 0
    address = 4001
    value = 0
    while(timestamp < 10):
        address_and_value = memory_trace.get_trace_entry(timestamp)
        value = ra_memory.get_value(address)
        assert address_and_value[0] == address
        assert address_and_value[1] == value
        assert value == value
        timestamp += 1
        address += 8
        value += 100


@pytest.mark.parametrize("num_addresses, value_size, block1_size, block2_size",
                         [(10, 20, 5, 5)])
def test_block_memory_contents(num_addresses, value_size, block1_size, block2_size):
    max_unit = 1 << value_size
    result = dict()
    for i in range(0, block1_size):
        result[i] = random.randint(0, RAND_MAX) % max_unit
    for i in range(0, block2_size):
        result[num_addresses//2+i] = random.randint(0, RAND_MAX) % max_unit


@pytest.mark.parametrize("num_addresses, value_size, num_filled",
                         [(10, 20, 5)])
def test_random_memory_contents(num_addresses, value_size, num_filled):
    max_unit = 1 << value_size
    unfilled = list()
    for i in range(0, num_addresses):
        unfilled.append(i)

    result = dict()
    for i in range(0, num_filled):
        i = i + random.randint(0, RAND_MAX) % len(unfilled)
        result[i] = random.randint(0, RAND_MAX) % max_unit
        unfilled.remove(unfilled[i % len(unfilled)])

def test_tinyram_opcode():
    assert pyzpk.tinyram_opcode.tinyram_opcode_AND    == 0b00000
    assert pyzpk.tinyram_opcode.tinyram_opcode_OR     == 0b00001
    assert pyzpk.tinyram_opcode.tinyram_opcode_XOR    == 0b00010
    assert pyzpk.tinyram_opcode.tinyram_opcode_NOT    == 0b00011
    assert pyzpk.tinyram_opcode.tinyram_opcode_ADD    == 0b00100
    assert pyzpk.tinyram_opcode.tinyram_opcode_SUB    == 0b00101
    assert pyzpk.tinyram_opcode.tinyram_opcode_MULL   == 0b00110
    assert pyzpk.tinyram_opcode.tinyram_opcode_UMULH  == 0b00111
    assert pyzpk.tinyram_opcode.tinyram_opcode_SMULH  == 0b01000
    assert pyzpk.tinyram_opcode.tinyram_opcode_UDIV   == 0b01001
    assert pyzpk.tinyram_opcode.tinyram_opcode_UMOD   == 0b01010
    assert pyzpk.tinyram_opcode.tinyram_opcode_SHL    == 0b01011
    assert pyzpk.tinyram_opcode.tinyram_opcode_SHR    == 0b01100

    assert pyzpk.tinyram_opcode.tinyram_opcode_CMPE   == 0b01101
    assert pyzpk.tinyram_opcode.tinyram_opcode_CMPA   == 0b01110
    assert pyzpk.tinyram_opcode.tinyram_opcode_CMPAE  == 0b01111
    assert pyzpk.tinyram_opcode.tinyram_opcode_CMPG   == 0b10000
    assert pyzpk.tinyram_opcode.tinyram_opcode_CMPGE  == 0b10001

    assert pyzpk.tinyram_opcode.tinyram_opcode_MOV    == 0b10010
    assert pyzpk.tinyram_opcode.tinyram_opcode_CMOV   == 0b10011

    assert pyzpk.tinyram_opcode.tinyram_opcode_JMP    == 0b10100
    assert pyzpk.tinyram_opcode.tinyram_opcode_CJMP   == 0b10101
    assert pyzpk.tinyram_opcode.tinyram_opcode_CNJMP  == 0b10110

    assert pyzpk.tinyram_opcode.tinyram_opcode_10111  == 0b10111
    assert pyzpk.tinyram_opcode.tinyram_opcode_11000  == 0b11000
    assert pyzpk.tinyram_opcode.tinyram_opcode_11001  == 0b11001

    assert pyzpk.tinyram_opcode.tinyram_opcode_STOREB == 0b11010
    assert pyzpk.tinyram_opcode.tinyram_opcode_LOADB  == 0b11011
    assert pyzpk.tinyram_opcode.tinyram_opcode_STOREW == 0b11100
    assert pyzpk.tinyram_opcode.tinyram_opcode_LOADW  == 0b11101
    assert pyzpk.tinyram_opcode.tinyram_opcode_READ   == 0b11110
    assert pyzpk.tinyram_opcode.tinyram_opcode_ANSWER == 0b11111

def test_tinyram_opcode_args():
    assert pyzpk.tinyram_opcode_args.tinyram_opcode_args_des_arg1_arg2 == 1
    assert pyzpk.tinyram_opcode_args.tinyram_opcode_args_des_arg2 == 2
    assert pyzpk.tinyram_opcode_args.tinyram_opcode_args_arg1_arg2 == 3
    assert pyzpk.tinyram_opcode_args.tinyram_opcode_args_arg2 == 4
    assert pyzpk.tinyram_opcode_args.tinyram_opcode_args_none == 5
    assert pyzpk.tinyram_opcode_args.tinyram_opcode_args_arg2_des == 6