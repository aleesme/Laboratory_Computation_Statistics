#ifndef func_h
#define func_h

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

using namespace std;

// FUNZIONE PER LEGGERE IL FILE DELLE COORDINATE
void ReadFile (std::vector<double> &v1, std::vector<double> &v2, const std::string & file_name);

// PARABOLA PER IL FIT
double parabola (double * x, double * par);

// FUNZIONE CHE TROVA IL MASSIMO DI UNA TF1
double SezioneAureaMax (TF1 & f , double x0, double x1, double resolution);

#endif
