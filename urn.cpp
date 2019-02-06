/*************************** urn.cpp **********************************
* Author:        Yan  Zhang
* Date created:  2019
* Last modified: 2019-02-06
* Project:       Py-BiasedUrn
* Description:
* Python interface to univariate noncentral hypergeometric distributions
* GNU General Public License http://www.gnu.org/licenses/gpl.html
*****************************************************************************/

#include "stocc.h"
#include <Python.h>

 
PyObject* dWNCHypergeo(int * px, int nres, int m1, int m2, int n, double odds, double prec)
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
   
PyObject* PList = PyList_New(0);
    
    for (i=0; i < nres; i++) 
    {
        PyList_Append(PList, PyFloat_FromDouble(presult[i]));
      }	

      free(presult);
    return PList;



}




