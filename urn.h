/* urn.h
*
*
*
*/

#include "stocc.h"

// double * tdWNCHypergeo(int * px, int m1, int m2, int n, double odds, double prec, int nres);
PyObject* dWNCHypergeo(int * px, int nres, int m1, int m2, int n, double odds, double prec);
