#include "lib.h"


// FUNZIONE PER LEGGERE IL FILE DELLE COORDINATE
void ReadFile(vector<double> & v1, vector<double> & v2, const string & file_name)
{
	double x=0.;
	double y=0.;	
	ifstream file;
	
	file.open(file_name.c_str());
	while(true)
	{
		file >> x;
		file >> y;		
		if(file.eof() == true) break;		
		v1.push_back(x);
		v2.push_back(y);
	}	
	file.close();
	
	return;
}

// PARABOLA PER IL FIT
double parabola (double * x, double * par)
{
	return par[0]*x[0]*x[0] + par[1]*x[0] + par[2];
}

// FUNZIONE CHE CALCOLA IL MASSIMO DI UNA TF1
double SezioneAureaMax (TF1 & f , double x0, double x1, double resolution)
{
	double r = 0.618;
	double x2 = 0.;
	double x3 = 0.;
	
	while (fabs(x1-x0) > resolution)
	{
		x2 = x0 + r*(x1-x0);
		x3 = x0 + (1.-r)*(x1-x0);
		
		if (f.Eval(x3)<f.Eval(x2)) x0 = x3;
		else x1 = x2;	
	}
	return (x1+x2)/2.;
}




