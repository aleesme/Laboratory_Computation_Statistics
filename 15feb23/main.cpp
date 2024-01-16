// c++ -o main main.cpp `root-config --glibs --cflags` montecarlo.cc

#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
//#include "TFitResult.h"
//#include "TString.h"

#include "statistiche_vector.h"
#include "montecarlo.h"


using namespace std ;


int main (int argc, char** argv)
{
	int N = 10000;
	int nBin = 0.5*sqrt(N);
	
	vector<double> unif;
	vector<double> para;
	
	// riempimento dell'istogramma per gli eventi gaussiani con TCL con uniforme
	TH1F h_gauss ("h_gauss", "gaussiana", nBin, 1., 3.);	
	for (int i=0; i<N; i++)
	{
		unif.push_back(rand_TCL_unif());
		h_gauss.Fill(unif.at(i));
	}

	// disegno dell'istogramma per gli eventi gaussiani con TCL con uniforme
	TCanvas c1;
	h_gauss.SetFillColor(kGreen);
	h_gauss.Draw();
	c1.Print("gaussiana.png", "png");
	
	
	// riempimento dell'istogramma per gli eventi della f(x) parabolica
	TH1F h_parab ("h_parab", "f(x)", nBin, 1., 3.);	
	for (int i=0; i<N; i++)
	{
		h_parab.Fill(rand_TAC());
	}

	// disegno dell'istogramma per gli eventi della f(x) parabolica
	h_parab.SetFillColor(kAzure+10);
	h_parab.Draw();
	c1.Print("parabola.png", "png");
	
	
	// riempimento dell'istogramma per gli eventi gaussiani con TCL con f(x)
	TH1F h_parab_TCL ("h_parab_TCL", "gaussiani", nBin, 1., 3.);	
	for (int i=0; i<N; i++)
	{
		para.push_back(rand_TCL_para());
		h_parab_TCL.Fill(para.at(i));
	}

	// disegno dell'istogramma per gli eventi gaussiani con TCL con f(x)
	h_parab_TCL.SetFillColor(kRed-10);
	h_parab_TCL.Draw();
	c1.Print("parabola_TCL.png", "png");
	
	// asimmetria e curtosi per il  quarto punto
	double asimmetria_unif = asimmetria(unif);
	double asimmetria_para = asimmetria(para);
	double curtosi_unif = curtosi(unif);
	double curtosi_para = curtosi(para);
	
	// andamento di asimmetria e curtosi per il quinto punto
	TGraph g_asimmetria_unif;
	TGraph g_asimmetria_para;
	TGraph g_curtosi_unif;
	TGraph g_curtosi_para;
	
	for (int n=2; n<5000; n=n*2)
	{
		vector<double> unif2;
		vector<double> para2;
		for (int j=0; j<N; j++)
		{
			unif2.push_back(rand_TCL_unif(n));
			para2.push_back(rand_TCL_para(n));
		}		
		g_asimmetria_unif.SetPoint(g_asimmetria_unif.GetN (), n, asimmetria(unif2));
		g_asimmetria_para.SetPoint(g_asimmetria_para.GetN (), n, asimmetria(para2));
		g_curtosi_unif.SetPoint(g_curtosi_unif.GetN (), n, curtosi(unif2));
		g_curtosi_para.SetPoint(g_curtosi_para.GetN (), n, curtosi(para2));			
	}
	
	g_asimmetria_unif.SetLineColor(kRed);
	g_asimmetria_para.SetLineColor(kBlue);
	g_curtosi_para.SetLineColor(kGreen);
	g_curtosi_unif.SetLineColor(kOrange-2);
	
	g_asimmetria_unif.Draw("ALP");
	g_asimmetria_para.Draw("LP SAME");
	c1.SetLogx ();
	c1.Print("asimmetria.png", "png");
	
	g_curtosi_unif.Draw("ALP");
	g_curtosi_para.Draw("LP SAME");
	c1.Print("curtosi.png", "png");	

	return 0;
}
