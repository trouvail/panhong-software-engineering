# -*- coding: UTF-8 -*-
"""
@Project ：最大子数组之积 
@File ：zyl_pylint.py
@Author ：hamlin-zhou
@Date ：2023/5/12 17:33
"""
import pylint.lint


pylint_opts = ['--rcfile=PylintConfig.conf', '-ry', './new_zyl.py']

pylint.lint.Run(pylint_opts)