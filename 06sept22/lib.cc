#include "lib.h"

// COSTRUTTORE DELLA CLASSE FUNC
func::func (double x0)
{
	m_x0 = x0;
	m_a = -3./(4.*x0*x0*x0);
	m_c = 3./(4.*x0);
}


// METODO CHE RESTITUISCE IL VALORE DELLA PDF
double func::eval (double x)
{
	if (-1.*m_x0<x<m_x0) return m_a*x*x + m_c;
	else return 0;
}


// FUNZIONE CHE GENERA NUMERI PSEUDOCASUALI COMPRESI TRA MIN E MAX SECONDO UNA DISTRIBUZIONE UNIFORME 
double rand_range (double min, double max)
{
	double x = (rand() / static_cast<double> (RAND_MAX))*(max-min) + min;
	return x;
}


// FUNZIONE CHE GENERA NUMERI PSEUDOCASUALI DISTRIBUITI SECONDO LA PDF PARABOLICA CON IL METODO TRY AND CATCH
double rand_parabola (func pdf, double x0)
{
	double x = 0.;
	double y = 0.;
	// ciclo che si ripete fino a trovare un punto che sta al di sotto della pdf	
	do
	{
		x = rand_range (-x0, x0);
		y = rand_range (0, pdf.eval(0));
	} while (y>pdf.eval(x));
	// ciclo che si ripete fino a trovare un punto che sta al di sotto della pdf		
	return x;
}


// FUNZIONE CHE CALCOLA LA MEDIA
double media (vector<double> const & campione)
{
	double somma = 0.;
	for (int i=0; i<campione.size(); i++)
	{
		somma += campione[i];
	}
	return somma/campione.size();
}
	
// FUNZIONE CHE CALCOLA LA SIGMA
double sigma (vector<double> const & campione)
{
	double somma = 0.;
	double somma_sq = 0.;
	for (int i=0 ; i<campione.size(); i++) 
	{
        	somma += campione[i];
        	somma_sq += campione[i]*campione[i];
	}
    	double varianza = somma_sq/campione.size() - (somma*somma)/(campione.size()*campione.size());
    	return sqrt(varianza);
}
    	
// FUNZIONE CHE CALCOLA L'ERRORE DELLA MEDIA
double errore_media (vector<double> const & campione)
{
    	return sigma(campione)/sqrt(campione.size());
}
    	
// FUNZIONE CHE CALCOLA L'ERRORE DELLA SIGMA
double errore_sigma (vector<double> const & campione)
{
    	return sigma(campione)*sigma(campione)* sqrt(2./((campione.size()-1)));
}





