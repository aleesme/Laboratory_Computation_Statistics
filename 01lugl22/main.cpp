// c++ -o main main.cpp `root-config --glibs --cflags` lib.cc

#include "lib.h"


int main (int argc, char ** argv)
{
	if (argc < 3)
   	{
      		cerr<<"uso del programma: "<<argv[0]<<" media sigma\n";
      		return 1 ;
    	}
	
	double media = atof(argv[1]);
	double sigma = atof(argv[2]);
	vector<double> mean_MQ;
	vector<double> mean_MV;
	vector<double> sigma_MQ;
	vector<double> sigma_MV;
	vector<double> entrate;
	
	double max_mean ;
  	double min_mean ;
  	double max_sigma ;
  	double min_sigma ;
	
	TCanvas c1;
	
	for (int k=4; k<100; k=k*2)
	{
		entrate.push_back(k);
				
		// riempimento del vector
		vector<double> campione;
		for (int i=0; i<k; i++)
		{
			campione.push_back(rand_gauss(fgaus, media, sigma));
		}

		// creazione dell'istogramma
		int Nbin = 50;
		double min = media-3.*sigma;
		double max = media+3.*sigma;
		TH1F histo = MakeHisto (campione, Nbin, min, max);
		histo.SetFillColor(kGray);
		histo.GetXaxis()->SetTitle ("asse x") ;
		histo.GetYaxis()->SetTitle ("conteggi per bin") ;
		
		// fit con la gaussiana e riempimento dei vector con gli scarti dei parametri
		TFitResultPtr fit_MQ = histo.Fit ("gaus", "SQ"); // minimi quadrati	
		mean_MQ.push_back(histo.GetFunction("gaus")->GetParameter(1) - media);
		sigma_MQ.push_back(histo.GetFunction("gaus")->GetParameter(2) - sigma);
		histo.GetFunction("gaus")->SetLineColor (kGreen);
		histo.Draw();
		c1.Print(TString("gaussiani_") + k + TString(".png"),"png");	
		
		TFitResultPtr fit_MV = histo.Fit ("gaus", "LSQ"); // massima verosimiglianza
		mean_MV.push_back(histo.GetFunction("gaus")->GetParameter(1) - media);
		sigma_MV.push_back(histo.GetFunction("gaus")->GetParameter(2) - sigma);
		
		if (mean_MQ.back () < min_mean) min_mean = mean_MQ.back () ;
      		if (mean_MV.back () < min_mean) min_mean = mean_MV.back () ;
      		if (sigma_MQ.back () < min_sigma) min_sigma = sigma_MQ.back () ;
      		if (sigma_MV.back () < min_sigma) min_sigma = sigma_MV.back () ;
      		if (mean_MQ.back () > max_mean) max_mean = mean_MQ.back () ;
      		if (mean_MV.back () > max_mean) max_mean = mean_MV.back () ;
      		if (sigma_MQ.back () > max_sigma) max_sigma = sigma_MQ.back () ;
      		if (sigma_MV.back () > max_sigma) max_sigma = sigma_MV.back () ;
	}
	
	for (int i = 0 ; i < mean_MQ.size () ; ++i)
	{
      		cout << i << "\t"
           	<< entrate.at (i) << "\t"
           	<< mean_MQ.at (i) << "\t"
           	<< mean_MV.at (i) << "\n" ;
   	}	
	
	// creazione dei grafici degli scarti
	TGraph g_media_MQ (mean_MQ.size(), & entrate[0], & mean_MQ[0]);
	g_media_MQ.SetLineColor(kAzure);
	 
	TGraph g_sigma_MQ (sigma_MQ.size(), & entrate[0], & sigma_MQ[0]);
	g_sigma_MQ.SetLineColor(kAzure);
	
	TGraph g_media_MV (mean_MV.size(), & entrate[0], & mean_MV[0]);
	g_media_MV.SetLineColor(kRed);
	
	TGraph g_sigma_MV (sigma_MV.size(), & entrate[0], & sigma_MV[0]);
	g_sigma_MV.SetLineColor(kRed); 


	// disegno dei grafici sovrapposti
	c1.DrawFrame (entrate.at (0) - 1, min_mean, entrate.back () + 1, max_mean) ;
	g_media_MQ.Draw("L*");
	g_media_MV.Draw("L*");
	c1.Print("scarti_medie.png","png");
	
	c1.DrawFrame (entrate.at (0) - 1, min_sigma, entrate.back () + 1, max_sigma) ;
	g_sigma_MQ.Draw("L*");
	g_sigma_MV.Draw("L*");
	c1.Print("scarti_sigma.png","png");
	
		
	
	return 0;
}
