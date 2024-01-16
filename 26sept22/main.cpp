// c++ -o main main.cpp `root-config --glibs --cflags` lib.cc

#include "lib.h"

int main (int argc, char ** argv)
{
	// riempio i vettori con i valori letti nel file
	vector<double> x;
	vector<double> y;
	ReadFile(x, y, "coordinate.txt");
	
	// creo il TGraph per il disegno dei punti
	TGraph traiettoria(x.size(), & x[0], & y[0]);
	
	// faccio il fit con la parabola
  	TF1 fit ("fit", parabola, 0., 2., 3);
  	fit.SetLineWidth (2) ;
  	fit.SetLineStyle (7) ;
  	fit.SetLineColor (kGreen + 2) ;
  	TFitResultPtr fit_result = traiettoria.Fit (&fit, "S");  	
  	
  	// controllo che il fit abbia avuto successo e salvo i parametri con il loro errore
  	cout << "Feedback sul risultato del fit: " << fit_result->Status() << endl ;
  	double a = fit.GetParameter(0);
  	double b = fit.GetParameter(1);
	double c = fit.GetParameter(2);
	
	cout<<"\n\n";
	
	// varianza e covarianza per il calcolo dell'errore sulla gittata
	double var_a = fit_result->CovMatrix (0,0);
	double var_b = fit_result->CovMatrix (1,1);
	double var_ab = fit_result->CovMatrix (0,1);
	
	// calcolo della gittata con il suo errore e stampa dei valori
	double gittata = -1. * b/a;
	double sigma_gittata = gittata*gittata*(var_b/(b*b) + var_a/(a*a) + var_ab/(a*b));	
	cout.precision(2);
	cout<<"Gittata: "<<gittata<<" +/- "<<sigma_gittata<<endl;
	
	// calcolo del punto massimo e stampa dei valori
	double xMax = SezioneAureaMax(fit, 0., gittata, 0.0001);
	double yMax = fit.Eval(xMax);
	cout<<"Punto di massimo: ("<<xMax<<","<<yMax<<")"<<endl;	
		
	// disegno del fit
	TCanvas c1;	  	
  	traiettoria.SetTitle("traiettoria");
	traiettoria.GetXaxis()->SetTitle("x");
	traiettoria.GetYaxis()->SetTitle("y");
	traiettoria.SetMarkerStyle(4);
	traiettoria.SetMarkerColor(kPink+10);	
	traiettoria.Draw("AP SAME");
	c1.Print("traiettoria.png","png");
	

	return 0;
}


