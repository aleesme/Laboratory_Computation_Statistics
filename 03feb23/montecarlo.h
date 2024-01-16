#ifndef montecarlo_h
#define montecarlo_h

#include "lib.h"


// GENERA NUMERI SECONDO UNA DISTRIBUZIONE UNIFORME COMPRESI TRA MIN E MAX
double rand_range (double min, double max);


// GENERA NUMERI SECONDO UNA PDF CON IL METODO TRY AND CATCH
double rand_TAC (TF1 pdf, double xmin, double xmax, double ymax);


#endif




