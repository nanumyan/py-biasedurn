/*************************** stocR.cpp **********************************
* Author:        Vahan Nanumyan, Agner Fog
* Date created:  2006
* Last modified: 2019-02-06
* Project:       BiasedUrn
* Source URL:    github.com/nanumyan/py-biasedurn
*
* Description:
* Interface of non-uniform random number generators to Python implementation.
* This file contains source code for the class StocPyBase defined in stocPy.h.
*
* Copyright 2006-2011 by Agner Fog. 
* GNU General Public License http://www.gnu.org/licenses/gpl.html
*****************************************************************************/

#include "stocc.h"                     // class definition

/***********************************************************************
Fatal error exit (Replaces userintf.cpp)
***********************************************************************/

void FatalError(const char * ErrorText) {
   // This function outputs an error message and aborts the program.
   // TODO: UNTESTED!
   PyErr_SetString(PyExc_RuntimeError, ErrorText);             // Error exit in Python
}