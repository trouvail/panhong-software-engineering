# -*- coding: UTF-8 -*-
"""
@Project ：最大子数组之积
@File ：zyl_unittest.py
@Author ：hamlin-zhou
@Date ：2023/5/12 17:33
"""
import unittest
import new_zyl
import numpy as np
from unittest.mock import patch

class TestMaxProduct(unittest.TestCase):
    def test_maxProduct(self):
        self.assertEqual(new_zyl.maxProduct([2, 3, -2, 4]), 6)
        self.assertEqual(new_zyl.maxProduct([-2, 0, -1]), 0)
        self.assertEqual(new_zyl.maxProduct([1, 2, 3, 0, 4, 5]), 20)
        self.assertEqual(new_zyl.maxProduct([1, -2, 3, 0, 4, 5]), 20)
        self.assertEqual(new_zyl.maxProduct([1, -2, 3, -4, 5]), 120)
        self.assertEqual(new_zyl.maxProduct([-2]), -2)
        self.assertEqual(new_zyl.maxProduct([]), 0)

    def test_findMaxSubarray(self):
        self.assertEqual(new_zyl.findMaxSubarray([2, 3, -2, 4]), (6, [2, 3]))
        self.assertEqual(new_zyl.findMaxSubarray([-2, 0, -1]), (0, [0]))
        self.assertEqual(new_zyl.findMaxSubarray([1, 2, 3, 0, 4, 5]), (20, [1, 2, 3, 0, 4, 5]))
        self.assertEqual(new_zyl.findMaxSubarray([1, -2, 3, 0, 4, 5]), (20, [1, 2, 3, 0, 4, 5]))
        self.assertEqual(new_zyl.findMaxSubarray([1, -2, 3, -4, 5]), (60, [5]))
        self.assertEqual(new_zyl.findMaxSubarray([-2]), (-2, [-2]))
        self.assertEqual(new_zyl.findMaxSubarray([]), (0, []))

if __name__ == '__main__':
    # unittest.main()
    suite = unittest.TestSuite()

    tests = [TestMaxProduct("test_maxProduct"), TestMaxProduct("test_findMaxSubarray")]
    suite.addTests(tests)

    with open('./TestResult.txt','w') as file:
        runner = unittest.TextTestRunner(stream=file, verbosity=2)
        runner.run(suite)