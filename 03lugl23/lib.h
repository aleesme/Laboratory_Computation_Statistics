#ifndef lib_h
#define lib_h

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "TF1.h"
#include "TH1F.h"
#include "TFitResult.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

//FUNZIONE
double f (double x);

// FUNZIONE PER TF1
double f_R (double * x, double * par);

// FUNZIONE G PER TF1
double g_R (double * x, double * par);

// DISTRIBUZIONE UNIFORME
double rand_range (double min, double max);

// DISTRIBUZIONE GAUSSIANA
float rand_TCL (double mean, double sigma, int N=10);


#endif
