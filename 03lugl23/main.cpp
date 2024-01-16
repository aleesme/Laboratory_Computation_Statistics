// c++ -o main main.cpp `root-config --glibs --cflags` lib.cc

#include "TString.h"
#include "lib.h"

using namespace std;


// SCALARE L'ISTOGRAMMA
double scale_histo (TH1F & histo)
{
  double altezza = histo.GetBinContent (histo.GetMaximumBin ()) ;
  histo.Scale (1. / altezza) ;
  return altezza ;
}


// FUNZIONE CHE ESEGUE IL FIT, LO VISUALIZZA E RIEMPIE I DUE ISTOGTRAMMI COON I VALORI DI Q^2 E P-VALUE
void MakeFit (TF1 & f_fit, TH1F & h_Q2, TH1F & h_pvalue, int Ntoy, TString title)
{
	vector<double> x={0.5,1.5,2.5,3.5};	
	vector<double> sx (x.size(), 0.);
	vector<double> sy (x.size(), 0.2);

	// ciclo sui toy
	for (int i=0; i<Ntoy; i++)
	{
		// generazione dei punti
		vector<double> y;
		double epsilon=0.;
		for (double k=0.5; k<4; k=k+1.)
		{
			epsilon=rand_TCL(0., 0.2);
			y.push_back(f(k) + epsilon);
		}	
		TGraphErrors grafico (x.size(), &x[0], &y[0], &sx[0], &sy[0]);
		
		// fit
		TFitResultPtr fit_result = grafico.Fit (&f_fit, "SQ");
		int check = fit_result->Status (); // controllo del successo del fit
		if(check>0) cout << "WARNING: " << check << " fits did not succeed\n" ;
		
		// disegno del fit solo per il primo toy		
		if(i==0)
		{
			TCanvas c1;
			f_fit.SetLineColor(kGreen);
			grafico.SetMarkerColor(kBlack);
			grafico.SetMarkerStyle (20) ;
			grafico.SetMarkerSize (0.8) ;
			grafico.Draw("AP");
			c1.Print(title + ".gif","gif");
		}
		
		// riempimento degli istogrammi
		h_Q2.Fill(fit_result->Chi2 ());
		h_pvalue.Fill(fit_result->Prob ());
	}
	// ciclo sui toy
}


int main (int argc, char** argv)
{
	int Ntoy = 100;	
	
	// fit con f
	TH1F h_Q2_f("h_Q2_f", "distribuzione Q^2", Ntoy/4, 0., 5.); 
	TH1F h_pvalue_f("h_pvalue_f", "distribuzione p-value", Ntoy/4, 0., 1.);
	TF1 f_fit("f_fit", f_R, 0., 4., 2);
	MakeFit (f_fit, h_Q2_f, h_pvalue_f, Ntoy, "campioneF");
	
	// disengo degli istogrammi
	TCanvas c1;
	h_Q2_f.Draw();
	c1.Print("ChiQuadro_f.png", "png");
	h_pvalue_f.Draw();
	c1.Print("pvalue_f.png", "png");


	// fit con g
	TH1F h_Q2_g("h_Q2_g", "distribuzione Q^2", Ntoy/4, 100., 150.); 
	TH1F h_pvalue_g("h_pvalue_g", "distribuzione p-value", Ntoy/4, 0., 0.0000001);
	TF1 g_fit("g_fit", g_R, 0., 4., 2);
	MakeFit (g_fit, h_Q2_g, h_pvalue_g, Ntoy, "campioneG");
	
	// disengo degli istogrammi
	h_Q2_g.Draw();
	c1.Print("ChiQuadro_g.png", "png");
	h_pvalue_g.Draw();
	c1.Print("pvalue_g.png", "png");

	// confronto degli istogrammi
	//c1.SetLogx();
	h_Q2_g.SetLineColor (kRed) ;
	h_Q2_g.Draw ("hist") ;
  	h_Q2_f.Draw ("hist same") ;
  	c1.Print ("confronto.gif", "gif") ;

	return 0;
}



