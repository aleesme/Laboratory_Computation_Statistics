#include "lib.h"

// GAUSSIANA
double fgaus (double x, double mean, double sigma) 
  {
    return exp (-1 * (x - mean) * (x - mean) / (2 * sigma * sigma)) / (sigma * 2.50662827) ;  // sqrt (2 * pi)
  }


// FUNZIONE CHE GENERA NUMERI PSEUDO-CASUALI SECONDO UNA DISTRIBUZIONE UNIFORME COMPRESI TRA MIN E MAX
double rand_range (double min, double max)
{
	double x = (rand() / static_cast<double> (RAND_MAX))*(max-min) + min;
	return x;
}


// FUNZIONE PER LA GENERAZIONE DI NUMERI PSEUDO-CASUALI DISTRIBUITI SECONDO UNA GAUUSIANA
double rand_gauss (double f (double, double, double), double mean, double sigma)
  {
    double x = 0. ;
    double y = 0. ; 
    do {
      x = rand_range (mean - 4 * sigma, mean + 4 * sigma) ;
      y = rand_range (0, 1. / (sigma * 2.50)) ; // 2.50 ~ sqrt (2 * pi))
    } while (y > f (x, mean, sigma)) ;
    return x ; 
  }


// FUNZIONE PER CREARE L'ISTOGRAMMA
TH1F MakeHisto (const vector<double> & campione, int & N, double & min, double & max)
{
   	TH1F histo ("histo", "istogramma", N, min, max);
	// riempimento dell'istogramma
  	for (int i=0; i<campione.size(); i++)
    	{
      		histo.Fill(campione.at (i));
    	}    	
  	return histo ;
}






