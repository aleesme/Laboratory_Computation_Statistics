// c++ -o main main.cpp `root-config --glibs --cflags` lib.cc

#include "lib.h"


int main (int argc, char ** argv)
{
	// controllo del corretto utilizzo del programma
	if (argc < 3)
    	{
      		cerr << "uso: " << argv[0] << " x_zero numero_eventi" << endl ;
      		exit (1) ;
    	}
    	
    	// parametri di ingresso
	double x0 = atof(argv[1]);
	double N = atoi(argv[2]);
	
	
	func pdf (x0);
	vector<double> campione;
	TH1F histo ("histo", "pdf parabolica", sqrt(N), -1.*x0, x0);
	
	
	// ciclo per riempire il vector e l'istogramma con numeri pseudocasuali distribuiti secondo la pdf
	for (int i=0; i<N; i++)
	{
		campione.push_back(rand_parabola(pdf, x0));
		histo.Fill(campione.at(i));
	}
	// ciclo per riempire il vector e l'istogramma con numeri pseudocasuali distribuiti secondo la pdf


	// disegno dell'istogramma
	TCanvas c1;
	histo.GetXaxis()->SetTitle ("asse x");
	histo.GetYaxis()->SetTitle ("conteggi");
	histo.SetFillColor (kPink + 1);	
	histo.Draw();	
	c1.Print ("campione.png","png");
	
	// stampa della media e della sigma della distribuzione con i rispettivi errori
	cout<<"Media: "<<media(campione)<<" +/- "<<errore_media(campione)<<endl;
	cout<<"Sigma: "<<sigma(campione)<<" +/- "<<errore_sigma(campione)<<endl;
	
	
	
	return 0;
}





