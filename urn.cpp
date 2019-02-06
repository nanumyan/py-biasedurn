/*************************** urn.cpp **********************************
* Author:        Yan  Zhang
* Date created:  2006
* Last modified: 2019-02-06
* Project:       Py-BiasedUrn
* Description:
* Python interface to univariate noncentral hypergeometric distributions
* GNU General Public License http://www.gnu.org/licenses/gpl.html
*****************************************************************************/

#include "stocc.h"
#include <Python.h>
//#include "wnchyppr.cpp"
//#include "fnchyppr.cpp"
//#include "mersenne.cpp"
//#include "randomc.h"
//#include "mother.cpp"
//#include "userintf.cpp"
//#include "stoc1.cpp"
 
double * tdWNCHypergeo(int * px, int m1, int m2, int n, double odds, double prec, int nres)
{
   int     N    = m1 + m2;             // Total number of balls
   double* buffer = 0;                 // Table of probabilities
   int     BufferLength;               // Length of table
   int     x;                          // Temporary x
   int     x1, x2;                     // Table limits
   int     xmin, xmax;                 // Absolute limits for x
   int     i;                          // Loop counter

   // Check validity of parameters
//   if (odds < 0) error("Invalid value for odds");
 //  if (m1 < 0 || m2 < 0 || n < 0) error("Negative parameter");
//   if ((unsigned int)N > 2000000000) error("Overflow");
//   if (n > N) error ("n > m1 + m2: Taking more items than there are");
//   if (n > m2 && odds == 0) error ("Not enough items with nonzero weight");
//   if ( prec < 0 || prec > 1) prec = 1E-7;

   // Allocate result vector
   double * presult;
   presult=(double*)malloc(nres*sizeof(double));
   
   // Make object for calculating probabilities
   CWalleniusNCHypergeometric wnc(n, m1, N, odds, prec);

   // Check if it is advantageous to use MakeTable:
   if (nres > 1 &&
   (BufferLength = wnc.MakeTable(buffer, 0, &x1, &x2),
   x1)) {
      // Use MakeTable
      xmin = m1 + n - N;  if (xmin < 0) xmin = 0;  // Minimum x
      xmax = n;  if (xmax > m1) xmax = m1;         // Maximum x

      // Allocate buffer
      buffer = (double*)malloc(BufferLength*sizeof(double));
      // Make table of probabilities
      wnc.MakeTable(buffer, BufferLength, &x1, &x2, prec*0.001);
      // Get probabilities from table
      for (i = 0; i < nres; i++) {
         x = px[i];
         if (x >= x1 && x <= x2) {
            // x within table
            presult[i] = buffer[x - x1];              // Get result from table
         }
         else if (x >= xmin && x <= xmax) {
            // Outside table. Result is very small but not 0
            presult[i] = wnc.probability(x);          // Calculate result
         }
         else {
            // Impossible value of x
            presult[i] = 0.;                          // Result is 0
         }
         // if (ilog) presult[i] = log(presult[i]);   // Log desired
      }
   }
   else {
      // Calculate probabilities one by one
      for (i = 0; i < nres; i++) {
         presult[i] = wnc.probability(px[i]);
         //if (ilog) presult[i] = log(presult[i]);
      }
   }
   // Return result
   return presult;
}


static PyObject *dWNCHypergeo(PyObject *self, PyObject *args)
{

PyObject* seq;
int *px;
int seqlen;
int i;
int m1,m2,n;
double odds,prec;

if(!PyArg_ParseTuple(args, "Oiiidd", &seq,&i,&m1,&m2,&n,&odds,&prec))
        return 0;
seq = PySequence_Fast(seq, "argument must be iterable");
if(!seq)
        return 0;

    seqlen = PySequence_Fast_GET_SIZE(seq);
    px = (int *)malloc(seqlen*sizeof(double));
    if(!px) {
        Py_DECREF(seq);
        return PyErr_NoMemory(  );
    }

 for(i=0; i < seqlen; i++) {
        PyObject *fitem;
        PyObject *item = PySequence_Fast_GET_ITEM(seq, i);
        if(!item) {
            Py_DECREF(seq);
            free(px);
            return 0;
        }
        fitem = PyNumber_Float(item);
        if(!fitem) {
            Py_DECREF(seq);
            free(px);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return 0;
        }
        px[i] = PyFloat_AS_DOUBLE(fitem);
        Py_DECREF(fitem);
    }    

    /* clean up, compute, and return result */
    Py_DECREF(seq);

  double *result;
  result=tdWNCHypergeo(px, m1, m2, n, odds, prec, seqlen);


  PyObject* PList = PyList_New(0);
    
    for (i=0; i < seqlen; i++) 
    {
        PyList_Append(PList, PyFloat_FromDouble(result[i]));
      }	

      free(result);
    return PList;
}


//static PyMethodDef totalMethods[] = {
//    {"dWNCHypergeo", dWNCHypergeo, METH_VARARGS, "Sum a sequence of numbers."},
//    {0} /* sentinel */
//};



//static struct PyModuleDef BiasedUrn_module = {
//   PyModuleDef_HEAD_INIT,
//   "BiasedUrn",   /* name of module */
//   NULL, /* module documentation, may be NULL */
//   -1,       /* size of per-interpreter state of the module,
//                or -1 if the module keeps state in global variables. */
//   totalMethods
//};


