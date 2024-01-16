// MOMENTI : INSIEME DI FUNZIONI CHE RICEVONO COME ARGOMENTO UN VECTOR CONTENENTE UN CAMPIONE E NE CALCOLANO LE STATISTICHE

#include "momenti.h"

// MEDIA
double media (std::vector<double> const & campione)
{
	double somma = 0.;
	for (int i=0; i<campione.size(); i++)
	{
		somma += campione[i];
	}
	return somma/campione.size();	
}

// VARIANZA
double varianza (std::vector<double> const & campione)
{
	double somma = 0.;
	double somma_sq = 0.;
	for (int i=0 ; i<campione.size(); i++) 
	{
        	somma += campione[i];
        	somma_sq += campione[i]*campione[i];
	}
    	return somma_sq/campione.size() - (somma*somma)/(campione.size()*campione.size());
}

// DEVIAZIONE STANDARD
double Sigma (std::vector<double> const & campione)
{
	return sqrt(varianza(campione));
}

// SKEWENESS
double skeweness (std::vector<double> const & campione)
{
	double mediaV = media(campione);
    	double asimmV = 0.;
    	for (int i = 0 ; i < campione.size () ; ++i) 
	{
        	asimmV += pow ((campione[i] - mediaV), 3.);
      	}
    	return asimmV / (campione.size() * pow(Sigma(campione), 3.));
}

// CURTOSI
double curtosi (std::vector<double> const & campione)
{
	double mediaV = media(campione);
    	double curtosiV = 0. ;
    	for (int i = 0 ; i < campione.size () ; ++i) 
      	{
        	curtosiV += pow ((campione[i] - mediaV), 4.) ;
     	}
    	return curtosiV / (campione.size () * varianza (campione) * varianza (campione)) - 3.;
}
