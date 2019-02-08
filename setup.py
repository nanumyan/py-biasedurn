#!/usr/bin/env python

"""
setup.py file for Python BiasedUrn
"""

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup
# from distutils.core import setup, Extension


cpp_dir = "biasedurn/cpp_src/"
cpp_source_files = [
    'core.i',
    'urn.cpp', 
    'stoc3.cpp', 'stoc2.cpp', 'stoc1.cpp', 
    'wnchyppr.cpp', 'fnchyppr.cpp', 
    'mersenne.cpp', 'mother.cpp',
    #'erfres.cpp', 'erfresmk.cpp',
    'userintf.cpp'
]
sources = [cpp_dir+file for file in cpp_source_files]

biasedurn_extension = Extension('biasedurn.cpp_src._core',
                            define_macros = [#('PY_BUILD', ), TEMPORARY
                                ('MAXCOLORS', 10000000)],
                            include_dirs = [cpp_dir],
                            sources = sources,
                            swig_opts = ['-c++']
                            )

with open("README.md", "r") as fh:
    long_description = fh.read()

setup (name = 'biasedurn',
       version = '0.0.2',
       author = "Vahan Nanumyan",
       author_email='',
       url = "",
       classifiers = [
           "Development Status :: 1 - Planning",
           "Intended Audience :: Science/Research",
           "Topic :: Scientific/Engineering :: Mathematics",
           "Topic :: Scientific/Engineering :: Information Analysis",
           "Topic :: Scientific/Engineering :: Bio-Informatics",
           "License :: OSI Approved :: GNU General Public License v3 (GPLv3)"
           ],
       keywords='probability distribution RNG non-central multivariate hypergeometric Wallenius Fisher multinomial',
       description = """BiasedUrn provides discrete distributions in Python""",
       long_description = long_description,
       long_description_content_type = "text/markdown",
       project_urls={ 
        'Bug Reports': 'https:'
       },
    #    packages = ['biasedurn'],
       ext_modules = [biasedurn_extension],
       py_modules = ["biasedurn.cpp_src.core"],
       )