// DEFINIZIONE DELLA CLASSE ARRAY

#include <iostream>
#ifndef array_h
#define array_h


class array
{
public:
	array (int dim); // costruttore che prende in input la dimensione dell'array
	~array (); // distruttore
	
	// restituisce true se l'indice passato è minore della dimensione del vettore
	bool check_idx(int idx) const;
	
	// riempie la cella di memoria corrispondente all'indice con il valore dell'elemento passato
	void riempi (int indice, double elemento);
	
	// restituisce l'elemento i-esimo del vettore
	double get (int idx);


private:
	double * m_ptr; // puntatore al primo elemento del vettore
	int m_dim; // dimensione del vettore

};

#endif


















