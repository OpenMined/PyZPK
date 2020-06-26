import random
import pytest
import pyzpk
import math

# simple test cases.
# 1. Insert some random address and values in the memory
# 2. Test whether the new insertion is not affecting already existing values.
def test_memory():
    memory_trace = pyzpk.memory_store_trace()
    ra_memory = pyzpk.ra_memory(10,10)
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