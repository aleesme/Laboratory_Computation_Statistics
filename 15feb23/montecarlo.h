#ifndef montecarlo_h
#define montecarlo_h

#include <iostream>
#include <cstdlib>

// DISTRIBUZIONE UNIFORME
double rand_range (double min, double max);

// DISTRIBUZIONE GAUSSIANA CON TEOREMA CENTRALE DEL LIMITE
double rand_TCL_unif (int N=10);

// PARABOLA
double parabola (double x);	

// GENERA NUMERI SECONDO LA PDF PARABOLICA CON IL METODO TRY AND CATCH (
double rand_TAC ();

// DISTRIBUZIONE f(x) CON TEOREMA CENTRALE DEL LIMITE
double rand_TCL_para (int N=10);

#endif




