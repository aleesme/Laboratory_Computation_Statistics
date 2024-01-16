#include "lib.h"

//FUNZIONE
double f (double x, double y)
{
  return exp (-1 * x) * cos (y);
}


// DISTRIBUZIONE UNIFORME
double rand_range (double min, double max)
{
	double x = (rand() / static_cast<double> (RAND_MAX))*(max-min) + min;
	return x;
}


// MINIMO DI UN VECTOR
double minimo (std::vector<double> & campione)
{
	double min = campione.at(0);
	for (int i=1; i<campione.size(); i++)
	{
		if(campione.at(i)<min) min=campione.at(i);
	}
	return min;
}


// MASSIMO DI UN VECTOR
double massimo (std::vector<double> & campione)
{
	double max = campione.at(0);
	for (int i=1; i<campione.size(); i++)
	{
		if(campione.at(i)>max) max=campione.at(i);
	}
	return max;
}








