import unittest
import torch

from _pyzpk import sum


class TestSum(unittest.TestCase):
    def test_list(self):
        """
        Test that it can sum two pytorch tensors.
        """
        x = torch.Tensor([2, 3.5])
        y = torch.Tensor([3, 2.5])
        result = sum(x, y).tolist()
        self.assertEqual(result, [5.0, 6.0])


if __name__ == "__main__":
    unittest.main()
