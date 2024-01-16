#include "montecarlo.h"


// DISTRIBUZIONE UNIFORME
double rand_range (double min, double max)
{
	double x = (rand() / static_cast<double> (RAND_MAX))*(max-min) + min;
	return x;
}


// DISTRIBUZIONE GAUSSIANA CON TEOREMA CENTRALE DEL LIMITE
double rand_TCL_unif (int N)
{					
	double media=0;
	for (int i=0; i<N; i++)
	{
		media += rand_range (1.,3.);		
	}
	return media/N;	
}


// PARABOLA
double parabola (double x)
{
	return (2-x)*(x-2)+1;
}


// GENERA NUMERI SECONDO LA PDF PARABOLICA CON IL METODO TRY AND CATCH
double rand_TAC ()
{
	double x=0.;
	double y=0.;
	double ymax = parabola(2.);
	// ciclo che si ripete fino a trovare un punto che sta al di sotto della pdf	
	do
	{
		x = rand_range (1., 3.);
		y = rand_range (0, ymax);
	} while (y>parabola(x));
	// ciclo che si ripete fino a trovare un punto che sta al di sotto della pdf		
	return x;
}


// DISTRIBUZIONE f(x) CON TEOREMA CENTRALE DEL LIMITE
double rand_TCL_para (int N)
{
	double media=0;
	for (int i=0; i<N; i++)
	{
		media += rand_TAC ();		
	}
	return media/N;	

}




