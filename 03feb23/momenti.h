// MOMENTI : INSIEME DI FUNZIONI CHE RICEVONO COME ARGOMENTO UN VECTOR CONTENENTE UN CAMPIONE E NE CALCOLANO LE STATISTICHE

#ifndef momenti_h
#define momenti_h
#include <cmath>
#include <vector>

// MEDIA
double media (std::vector<double> const & campione);

// VARIANZA
double varianza (std::vector<double> const & campione);

// DEVIAZIONE STANDARD
double Sigma (std::vector<double> const & campione);

// SKEWENESS
double skeweness (std::vector<double> const & campione);

// CURTOSI
double curtosi (std::vector<double> const & campione);

#endif


