#!/usr/bin/env python

"""
setup.py file for Python BiasedUrn
"""

from distutils.core import setup, Extension


biasedurn_module = Extension('_biasedurn',
                           define_macros = [#('PY_BUILD', ), TEMPORARY
                                ('MAXCOLORS', 10000000)],
                           sources=[
                                'biasedurn.i',
                                'urn.cpp', 
                                'stoc3.cpp', 'stoc2.cpp', 'stoc1.cpp', 
                                'wnchyppr.cpp', 'fnchyppr.cpp', 
                                'mersenne.cpp', #'mother.cpp',
                                'userintf.cpp'
                            ],
                           swig_opts=['-c++']
                           )

setup (name = 'biasedurn',
       version = '0.1',
       author      = "Vahan Nanumyan",
       description = """First try to bind biased urn to python""",
       ext_modules = [biasedurn_module],
       py_modules = ["biasedurn"],
       )