/* File: biasedurn.i */
%module biasedurn

%{
#define SWIG_FILE_WITH_INIT
#include "stocc.h"
%}


/***********************************************************************
Class StochasticLib3
***********************************************************************/

class StochasticLib3 : public StochasticLib1 {
   // This class can be derived from either StochasticLib1 or StochasticLib2.
   // Adds more probability distributions
public:
   StochasticLib3(int seed);           // Constructor
   void SetAccuracy(double accur);     // Define accuracy of calculations
   int32_t WalleniusNCHyp (int32_t n, int32_t m, int32_t N, double odds); // Wallenius noncentral hypergeometric distribution
   int32_t FishersNCHyp (int32_t n, int32_t m, int32_t N, double odds); // Fisher's noncentral hypergeometric distribution
   void MultiWalleniusNCHyp (int32_t * destination, int32_t * source, double * weights, int32_t n, int colors); // Multivariate Wallenius noncentral hypergeometric distribution
   void MultiComplWalleniusNCHyp (int32_t * destination, int32_t * source, double * weights, int32_t n, int colors); // Multivariate complementary Wallenius noncentral hypergeometric distribution
   void MultiFishersNCHyp (int32_t * destination, int32_t * source, double * weights, int32_t n, int colors); // Multivariate Fisher's noncentral hypergeometric distribution
   // subfunctions for each approximation method
protected:
   int32_t WalleniusNCHypUrn (int32_t n, int32_t m, int32_t N, double odds); // WalleniusNCHyp by urn model
   int32_t WalleniusNCHypInversion (int32_t n, int32_t m, int32_t N, double odds); // WalleniusNCHyp by inversion method
   int32_t WalleniusNCHypTable (int32_t n, int32_t m, int32_t N, double odds); // WalleniusNCHyp by table method
   int32_t WalleniusNCHypRatioOfUnifoms (int32_t n, int32_t m, int32_t N, double odds); // WalleniusNCHyp by ratio-of-uniforms
   int32_t FishersNCHypInversion (int32_t n, int32_t m, int32_t N, double odds); // FishersNCHyp by inversion
   int32_t FishersNCHypRatioOfUnifoms (int32_t n, int32_t m, int32_t N, double odds); // FishersNCHyp by ratio-of-uniforms

   // variables
   double accuracy;                                        // desired accuracy of calculations

   // Variables for Fisher
   int32_t fnc_n_last, fnc_m_last, fnc_N_last;             // last values of parameters
   int32_t fnc_bound;                                      // upper bound
   double fnc_o_last;
   double fnc_f0, fnc_scale;
   double fnc_a;                                           // hat center
   double fnc_h;                                           // hat width
   double fnc_lfm;                                         // ln(f(mode))
   double fnc_logb;                                        // ln(odds)

   // variables for Wallenius
   int32_t wnc_n_last, wnc_m_last, wnc_N_last;             // previous parameters
   double wnc_o_last;
   int32_t wnc_bound1, wnc_bound2;                         // lower and upper bound
   int32_t wnc_mode;                                       // mode
   double wnc_a;                                           // hat center
   double wnc_h;                                           // hat width
   double wnc_k;                                           // probability value at mode
   int UseChopDown;                                        // use chop down inversion instead
   #define WALL_TABLELENGTH  512                           // max length of table
   double wall_ytable[WALL_TABLELENGTH];                   // table of probability values
   int32_t wall_tablen;                                    // length of table
   int32_t wall_x1;                                        // lower x limit for table
};

