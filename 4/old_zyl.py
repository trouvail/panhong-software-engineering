# -*- coding: UTF-8 -*-
"""
@Project ：最大子数组之积
@File ：zyl.py
@Author ：hamlin-zhou
@Date ：2023/5/12 17:33
"""
from ast import literal_eval

import numpy as np

def max_product_subarray(nums):
    """
    寻找乘积最大的连续子数组
    :param nums: 整数数组
    :return: 最大子数组及其乘积
    """
    if not nums:
        return None, 0

    max_product = nums[0]
    max_start, max_end = 0, 0
    start, end = 0, 0
    product = 1

    for i, num in enumerate(nums):
        if num == 0:
            # 如果遇到0，重置起点和乘积
            start = i + 1
            product = 1
            continue

        product *= num
        if product > max_product:
            # 如果当前乘积比最大乘积大，更新最大乘积和子数组的起点和终点
            max_product = product
            max_start, max_end = start, i

        elif product == 0:
            # 如果当前乘积为0，重置起点和乘积
            start = i + 1
            product = 1

    return nums[max_start:max_end+1], max_product

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

zyl_ls = get_in();
result_list, result_num = max_product_subarray(zyl_ls)

print("最大子数组是：", result_list)
print("最大子数组的和是：", result_num)

    
