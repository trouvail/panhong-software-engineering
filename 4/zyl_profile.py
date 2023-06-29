# -*- coding: UTF-8 -*-
"""
@Project ：最大子数组之积
@File ：zyl_profile.py
@Author ：hamlin-zhou
@Date ：2023/5/12 17:33
"""
import yappi
import new_zyl
import numpy as np

yappi.clear_stats()

test1 = [np.random.randint(1, 1000) for i in range(100000)]
test2 = [np.random.rand() for i in range(100000)]

yappi.start()

max_product = new_zyl.maxProduct(test1)
max_subarray_product, max_subarray = new_zyl.findMaxSubarray(test1)

yappi.stop()

stats = yappi.convert2pstats(yappi.get_func_stats())
stats.sort_stats("cumulative")
stats.print_stats()

yappi.start()

max_product = new_zyl.maxProduct(test2)
max_subarray_product, max_subarray = new_zyl.findMaxSubarray(test2)

yappi.stop()

stats = yappi.convert2pstats(yappi.get_func_stats())
stats.sort_stats("cumulative")
stats.print_stats()