# Testing functionality for routing on an benes network and arbitrary-size (AS) Waksman network.

import pyzpk
import math

def test_benes(num_packets):
    permutation = pyzpk.integer_permutation(math.ceil(num_packets))
    while permutation.next_permutation():
        routing = pyzpk.get_benes_routing(permutation)
        assert pyzpk.valid_benes_routing(permutation, routing) == True

def test_as_waksman(num_packets):
    permutation = pyzpk.integer_permutation(num_packets)
    while permutation.next_permutation():
        routing = pyzpk.get_as_waksman_routing(permutation)
        assert pyzpk.valid_as_waksman_routing(permutation, routing) == True


if __name__ == "__main__":
    num_packets = 8
    for i in range(2, num_packets+1):
        test_as_waksman(i)
    test_benes(num_packets)
