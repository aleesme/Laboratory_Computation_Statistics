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

using namespace std;

// CLASSE PER IMPLEMENTARE LA PDF
class func
{
public:
	func (double x0);  // costruttore
	double eval (double x);  // metodo che restituisce il valore della pdf dato x
	
private:
	double m_x0;
	double m_a;
	double m_c;
};

// FUNZIONE CHE GENERA NUMERI PSEUDOCASUALI COMPRESI TRA MIN E MAX SECONDO UNA DISTRIBUZIONE UNIFORME 
double rand_range (double min, double max);


// FUNZIONE CHE GENERA NUMERI PSEUDOCASUALI DISTRIBUITI SECONDO LA PDF PARABOLICA CON IL METODO TRY AND CATCH
double rand_parabola (func pdf, double x0);

// FUNZIONE CHE CALCOLA LA MEDIA
double media (vector<double> const & campione);
	
// FUNZIONE CHE CALCOLA LA SIGMA
double sigma (vector<double> const & campione);
    	
// FUNZIONE CHE CALCOLA L'ERRORE DELLA MEDIA
double errore_media (vector<double> const & campione);
    	
// FUNZIONE CHE CALCOLA L'ERRORE DELLA SIGMA
double errore_sigma (vector<double> const & campione);






#endif
