# -*- coding: UTF-8 -*-
"""
@Project ：最大子数组之积
@File ：zyl.py
@Author ：hamlin-zhou
@Date ：2023/5/12 17:33
"""
from ast import literal_eval

import numpy as np

def maxProduct(nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    if not nums:
        return 0

    max_product = nums[0]
    min_product = nums[0]
    result = nums[0]

    for i in range(1, len(nums)):
        if nums[i] < 0:
            max_product, min_product = min_product, max_product

        max_product = max(nums[i], max_product * nums[i])
        min_product = min(nums[i], min_product * nums[i])

        result = max(result, max_product)

    return result

def findMaxSubarray(nums):
    """
    :type nums: List[int]
    :rtype: Tuple[int, List[int]]
    """
    if not nums:
        return 0, []

    max_product = float('-inf')
    max_start = 0
    max_end = 0

    start = 0
    end = 0
    product = 1

    while end < len(nums):
        product *= nums[end]

        while start < end and product < 0:
            product /= nums[start]
            start += 1

        if product > max_product:
            max_product = product
            max_start = start
            max_end = end + 1

        end += 1

    return max_product, nums[max_start:max_end]

def get_in():
    """
    输入函数，包括错误处理
    :return: 输入的矩阵
    """
    array_ls = []
    try:
        array_ls = literal_eval(input("请输入矩阵或向量，输入格式参照[1, 2 ,3]或[2, 3, -2, 4]:"))
    except (SyntaxError, ValueError):
        print("非法输入!")
    except TypeError:
        print("请按照格式输入！")
    if isinstance(array_ls, tuple):
        array_ls = list(array_ls)
    elif isinstance(array_ls, int):
        array_ls = [array_ls]
    if isinstance(array_ls, list):
        temp = np.array(array_ls)
        if len(temp.shape) == 1:
            for index in array_ls:
                try:
                    assert isinstance(index, (int, float))
                except AssertionError:
                    print("非法输入!")
        else:
            print("Sorry!本程序现在仅支持一维数组")
            return TypeError
    else:
        print("非法输入!")
        return TypeError
    return array_ls

if __name__ == '__main__':
    nums = [2, 3, -2, 4]
    # nums = get_in();
    max_product = maxProduct(nums)
    max_subarray_product, max_subarray = findMaxSubarray(nums)
    print("Max product: {}".format(max_product))
    print("Max subarray: {}".format(max_subarray))
    print("Max subarray product: {}".format(max_subarray_product))