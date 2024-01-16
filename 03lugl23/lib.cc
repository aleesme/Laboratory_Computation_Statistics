#include "lib.h"

//FUNZIONE
double f (double x)
{
  return (x-2)*(x-2)*(x-2)+3;
}


// FUNZIONE PER TF1
double f_R (double * x, double * par)
{
	return pow(x[0]-par[0], 3) + par[1];
}


// FUNZIONE G PER TF1
double g_R (double * x, double * par)
{
	return pow(x[0]-par[0], 2) + par[1];
}


// DISTRIBUZIONE UNIFORME
double rand_range (double min, double max)
{
	double x = (rand() / static_cast<double> (RAND_MAX))*(max-min) + min;
	return x;
}


// DISTRIBUZIONE GAUSSIANA
float rand_TCL (double mean, double sigma, int N)
  {
    double y = 0. ; 
    double xMin = mean - sqrt (3 * N) * sigma ;
    double xMax = mean + sqrt (3 * N) * sigma ;
    for (int i = 0 ; i < N ; ++i)
      y += rand_range (xMin, xMax) ;
    y /= N ;
    return y ;
  }
  


