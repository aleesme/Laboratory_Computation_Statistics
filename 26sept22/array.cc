// IMPLEMENTAZIONE DELLA CLASSE ARRAY

#include <cmath>
#include <iostream>
#include <fstream>
#include "array.h"


array::array (int dim)
{
	m_ptr = dim ? new double[dim] : nullptr;
	m_dim = dim;
}

	
array::~array () 
{
	delete [] m_ptr;
}


bool array::check_idx(int idx) const
{
	return idx < m_dim;
}


void array::riempi (int idx, double elemento)
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
	

double array::get (int idx)
{
	if (!check_idx(idx))
	{
        	throw std::out_of_range ("L'indice inserito è più grande della dimensione dell'array\n");
    	}
    	return m_ptr[idx];
}
	

