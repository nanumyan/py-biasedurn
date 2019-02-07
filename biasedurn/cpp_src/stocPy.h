/*/***************************** File: stocPy.h *****************************
* Author:        Vahan Nanumyan, Agner Fog
* Date created:  2019-02-06
* Last modified: 
* Project:       py-biasedurn
* Source URL:    github.com/nanumyan/py-biasedurn
*
* Description:
* 
* Examples:
* 
* Documentation:
* 
*
* © 2019 Vahan Nanumyan, Agner Fog. GNU General Public License www.gnu.org/copyleft/gpl.html
*******************************************************************************/

#ifndef STOC_PY_H
#define STOC_PY_H

#include <Python.h>
// #include <Rinternals.h>


/***********************************************************************
         Class StochasticLib1
***********************************************************************/

class StocRBase {
   // This class is used as base class for the random variate generating 
   // classes when used for the Python interface
public:
   StocRBase(int32 seed) {}                         // Constructor
   static void InitRan() {                          // Call this before first random number
      Py_Initialize();
      GetRNGstate();
      Py_Finalize();
      }
   static void EndRan() {                           // Call this after last random number
      PutRNGstate();}                               // From R.DLL
   double Random() {                                // output random float number in the interval 0 <= x < 1
      return unif_rand();}                          // From R.DLL
   double Normal(double m, double s) {              // normal distribution
      return norm_rand()*s + m;}                    // From R.DLL
   int32 Hypergeometric(int32 n, int32 m, int32 N); // hypergeometric distribution (stocR.cpp)
protected:
   int32 HypInversionMod (int32 n, int32 M, int32 N);  // hypergeometric by inversion searching from mode
   int32 HypRatioOfUnifoms (int32 n, int32 M, int32 N);// hypergeometric by ratio of uniforms method
   static double fc_lnpk(int32 k, int32 N_Mn, int32 M, int32 n); // used by Hypergeometric
};

#endif