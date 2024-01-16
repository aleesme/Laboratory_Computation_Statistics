// DEFINIZIONE DELLA CLASSE ARRAY

#include <iostream>
#ifndef mioarray_h
#define mioarray_h


class mioarray
{
public:
	mioarray (int dim); // costruttore che prende in input la dimensione dell'array
	~mioarray (); // distruttore
	
	// restituisce true se l'indice passato è minore della dimensione del vettore
	bool check_idx (int idx) const;
	
	// riempie la cella di memoria corrispondente all'indice con il valore dell'elemento passato
	void riempi (int indice, double elemento);
	
	// restituisce l'elemento i-esimo del vettore
	double get (int idx);


private:
	double * m_ptr; // puntatore al primo elemento del vettore
	int m_dim; // dimensione del vettore

};

#endif


















