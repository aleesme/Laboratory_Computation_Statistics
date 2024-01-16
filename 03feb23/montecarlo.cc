#include "montecarlo.h"


// GENERA NUMERI SECONDO UNA DISTRIBUZIONE UNIFORME COMPRESI TRA MIN E MAX
double rand_range (double min, double max)
{
	double x = (rand() / static_cast<double> (RAND_MAX))*(max-min) + min;
	return x;
}


// GENERA NUMERI SECONDO UNA PDF CON IL METODO TRY AND CATCH
double rand_TAC (TF1 pdf, double xmin, double xmax, double ymax)
{
	double x=0.;
	double y=0.;
	// ciclo che si ripete fino a trovare un punto che sta al di sotto della pdf	
	do
	{
		x = rand_range (xmin, xmax);
		y = rand_range (0, ymax);
	} while (y>pdf.Eval(x));
	// ciclo che si ripete fino a trovare un punto che sta al di sotto della pdf		
	return x;
}


