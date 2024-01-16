#ifndef lib_h
#define lib_h

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

#include "TF1.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TString.h"

using namespace std;

// GAUSSIANA
double fgaus (double x, double mean = 0, double sigma = 1) ;

// FUNZIONE CHE GENERA NUMERI PSEUDO-CASUALI SECONDO UNA DISTRIBUZIONE UNIFORME COMPRESI TRA MIN E MAX
double rand_range (double min, double max);

// FUNZIONE PER LA GENERAZIONE DI NUMERI PSEUDO-CASUALI DISTRIBUITI SECONDO UNA GAUUSIANA
double rand_gauss (double f (double, double, double), double mean, double sigma) ;

// FUNZIONE PER CREARE L'ISTOGRAMMA
TH1F MakeHisto (const vector<double> & campione, int & N, double & min, double & max);

#endif









