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
