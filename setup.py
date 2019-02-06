#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


biasedurn_module = Extension('_biasedurn',
                           sources=['biasedurn_wrap.cxx', 'stoc3.cpp', 'stoc2.cpp', 'stoc1.cpp', 'wnchyppr.cpp', 'fnchyppr.cpp', 'mersenne.cpp', 'mother.cpp', 'userintf.cpp'],
                           )

setup (name = 'biasedurn',
       version = '0.1',
       author      = "Vahan Nanumyan",
       description = """First try to bind biased urn to python""",
       ext_modules = [biasedurn_module],
       py_modules = ["biasedurn"],
       )