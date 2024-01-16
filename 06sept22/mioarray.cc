// IMPLEMENTAZIONE DELLA CLASSE mioarray

#include <cmath>
#include <iostream>
#include <fstream>
#include "mioarray.h"


mioarray::mioarray (int dim)
{
	m_ptr = dim ? new double[dim] : nullptr;
	m_dim = dim;
}

	
mioarray::~mioarray () 
{
	delete [] m_ptr;
}


bool mioarray::check_idx(int idx) const
{
	return idx < m_dim;
}


void mioarray::riempi (int idx, double elemento)
{
	if (check_idx(idx))
	{
		m_ptr[idx] = elemento;
		return;
	}
	else{
	std::cout << "L'indice inserito è più grande della dimensione dell'array" << std::endl;
	return;
	}
}
	

double mioarray::get (int idx)
{
	if (!check_idx(idx))
	{
        	throw std::out_of_range ("L'indice inserito è più grande della dimensione dell'array\n");
    	}
    	return m_ptr[idx];
}
	

