// c++ -o main main.cpp `root-config --glibs --cflags` lib.cc montecarlo.cc momenti.cc

#include "TH1F.h"
//#include "TGraph.h"
#include "TCanvas.h"
#include "TFitResult.h"
//#include "TString.h"

#include "lib.h"
#include "montecarlo.h"
#include "momenti.h"

using namespace std ;


int main (int argc, char** argv)
{
	// coefficienti parabola e gaussiana
	double a = -0.2;
	double b = 0.8;
	double c = 1.;
	double mu = 2.;
	double sigma = 0.25;
	
	// punti in cui si azzera la parabola
	double delta = b*b-4.*a*c;
	double x_dx = (-b-sqrt(delta))/(2.*a);
	double x_sx = (-b+sqrt(delta))/(2.*a);

	// definizione della funzione somma della parabola (fondo) con la gaussiana
	TF1 model ("model", "gaus(0)+pol2(3)", x_sx, x_dx);
	model.SetParameter(0, 2.);
	model.SetParameter(1, mu);
	model.SetParameter(2, sigma);
	model.SetParameter(3, c);
	model.SetParameter(4, b);
	model.SetParameter(5, a);
	
	// disegno della funzione
	TCanvas c2;
	model.SetLineColor(kRed);
 	model.Draw ();
  	c2.Print ("funzione.png","png") ;
  	
  	// inizializzazione dei vector
  	vector<double> v_norm;
  	vector<double> v_mu;
  	vector<double> v_sigma;
  	vector<double> v_c;
  	vector<double> v_b;
  	vector<double> v_a;
	
	// ciclo sui toy experiment
	for (int j=0; j<100; j++)
	{
		TH1F h_eventi ("h_eventi", "h_eventi", 50, x_sx, x_dx);
		// ciclo sugli eventi
		for (int i=0; i<1000; i++)
		{
			h_eventi.Fill (rand_TAC(model, x_sx, x_dx, model.Eval(2.)));	
		} // ciclo sugli eventi
		
		// fit parziale del segnale
		TF1 segnale_fit ("segnale_fit", "gaus", x_sx, x_dx);
		//segnale_fit.SetParameter(0, 2.);
		segnale_fit.SetParameter(1, mu);
		segnale_fit.SetParameter(2, sigma);
		TFitResultPtr fit_result_segnale = h_eventi.Fit ("segnale_fit", "SQ+", "", 1., 3.);
		if(j==0) cout << "Feedback sul risultato del fit: " << fit_result_segnale->Status() << endl;
		
		/* fit parziale del fondo
		TF1 fondo_fit ("fondo_fit", "pol2", x_sx, x_dx);
		segnale_fit.SetParameter(0, c);
		segnale_fit.SetParameter(1, b);
		segnale_fit.SetParameter(2, a);
		TFitResultPtr fit_result_fondo = h_eventi.Fit ("fondo_fit", "SQ+", "", -1., 1.);
		if(j==0) cout << "Feedback sul risultato del fit: " << fit_result_fondo->Status() << endl;*/
		
		// fit totale
		TF1 model_fit ("model_fit", "gaus(0)+pol2(3)", x_sx, x_dx);
		//model_fit.SetParameter(0, segnale_fit.GetParameter(0));
		model_fit.SetParameter(1, segnale_fit.GetParameter(1));
		model_fit.SetParameter(2, segnale_fit.GetParameter(2));
		TFitResultPtr fit_result_totale = h_eventi.Fit ("model_fit", "SQ+");
		if(j==0) cout << "Feedback sul risultato del fit: " << fit_result_totale->Status() << endl;
		/*model_fit.SetParameter(3, fondo_fit.GetParameter(0));
		model_fit.SetParameter(4, fondo_fit.GetParameter(1));
		model_fit.SetParameter(5, fondo_fit.GetParameter(2));*/
		
		// riempimento dei vector
		v_norm.push_back(model_fit.GetParameter(0));
		v_mu.push_back(model_fit.GetParameter(1));
		v_sigma.push_back(model_fit.GetParameter(2));
		v_c.push_back(model_fit.GetParameter(3));
		v_b.push_back(model_fit.GetParameter(4));
		v_a.push_back(model_fit.GetParameter(5));
	
		// disegno del fit dell'istogramma per il primo toy
		if (j==0)
		{
			TCanvas c1;
			h_eventi.SetFillColor(kGreen);
			h_eventi.GetFunction("model_fit")->SetLineColor(kBlack);
			h_eventi.Draw();
			c1.Print("istogramma.png", "png");
		}
	} // ciclo sui toy experiment
	
	cout<<"Normalizzazione: 2.0\t"<<media(v_norm)<<" +/- "<<Sigma(v_norm)<<endl;
	cout<<"Media: "<<mu<<"\t"<<media(v_mu)<<" +/- "<<Sigma(v_mu)<<endl;
	cout<<"Sigma: "<<sigma<<"\t"<<media(v_sigma)<<" +/- "<<Sigma(v_sigma)<<endl;
	cout<<"A: "<<a<<"\t"<<media(v_a)<<" +/- "<<Sigma(v_a)<<endl;
	cout<<"B: "<<b<<"\t"<<media(v_b)<<" +/- "<<Sigma(v_b)<<endl;
	cout<<"C: "<<c<<"\t"<<media(v_c)<<" +/- "<<Sigma(v_c)<<endl;


	return 0;
}

