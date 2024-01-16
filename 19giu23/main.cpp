// c++ -o main main.cpp `root-config --glibs --cflags` lib.cc

#include "TH1F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
//#include "TFitResult.h"
//#include "TString.h"

#include "lib.h"

using namespace std;

// CALCOLO DELL'INTEGRALE COL METODO HIT OR MISS
vector<double> calc_integral (int nPunti)
{
	vector<double> risultato;
	int nhit = 0;
	double V = M_PI*M_E*1.;
	
	for (int i=0; i<nPunti; i++)
	{
		double x = rand_range (0, M_E);
		double y = rand_range (-M_PI/2, M_PI/2);
		double z = rand_range(0., 1.);		
		if (z<f(x,y)) nhit++;
	}
	
	double p = nhit / static_cast<double>(nPunti) ;
	risultato.push_back(V*p);
	risultato.push_back(sqrt(V*V*p*(1-p) / static_cast<double>(nPunti)));
	return risultato;
}


int main (int argc, char** argv)
{
	if (argc < 3)
	{
		cerr << "uso del programma: " << argv[0]<< " n_eventi n_toy\n" ;  
		return 1 ;
    	}	
	int N =	atoi(argv[1]);
	int Ntoy = atoi (argv[2]);
	
	
	// SECONDA RICHIESTA: prima stima dell'integrale
	vector<double> risultato = calc_integral(1000);
	
	
	// TERZA RICHIESTA: istogramma 
	TH1F h_int ("h_int", "histo", Ntoy/4, risultato.at(0)-3*risultato.at(1), risultato.at(0)+3*risultato.at(1));
	for (int i=0; i<Ntoy; i++)
	{
		h_int.Fill(calc_integral(1000).at(0));
	}
	
	// disegno dell'istogramma
	TCanvas c1;
	h_int.SetFillColor(kAzure-10);
	h_int.Draw();
	c1.Print("h_integrale.png", "png");
	
	// confronto
	cout<<"Integrale con istogramma: "<<h_int.GetMean()<<" +/- "<<h_int.GetRMS()<<endl;
	cout<<"Integrale con metodo hit or miss: "<<risultato.at(0)<<" +/- "<<risultato.at(1)<<endl;
	
	
	// QUINTA RICHIESTA: andamento dell'integrale e del suo errore
	TGraphErrors g_integrale;
	
	int index=0;
	for (int i=2; i<5000; i=i*2)
	{
		g_integrale.SetPoint(index, i, calc_integral(i).at(0));
		g_integrale.SetPointError(index, 0., calc_integral(i).at(1));
		index++;
	}
	
	g_integrale.SetMarkerStyle (20) ;
	g_integrale.SetMarkerColor (kAzure+3) ;
	g_integrale.SetLineColor (kAzure+10) ;
	g_integrale.SetMarkerSize (1) ;
	g_integrale.GetHistogram ()->GetXaxis ()->SetTitle ("numero di eventi") ;
	g_integrale.GetHistogram ()->GetYaxis ()->SetTitle ("integrale") ;
	g_integrale.SetLineWidth (3) ;
	
	c1.SetLogx();
	g_integrale.Draw("AL*");
	c1.Print("andamento.png", "png");	

	return 0;
}











