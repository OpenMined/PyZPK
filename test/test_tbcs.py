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


