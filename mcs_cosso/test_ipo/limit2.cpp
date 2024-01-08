//calcolo confidence level
//volgiamo vedere ual'è il massimo numero di eventi in eccesso cosi che rimanga compatibile con la mia ipotesi (vogliamo caloclare il confidence level dell ipotesi del segnale di fondo)












//USARE L ESERCIIZO D' ESAME CHE HA IL CALCOLO DELL INTERVALLO COMPLETO
#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TH1D.h>
#include <TMath.h>

using namespace std;

int main(){

  double nbkg = 44.7; 

  TApplication app("app",NULL,NULL);

  TH1D *h = new TH1D("h","",80,0,40);
  TH1D *hreg = new TH1D("hreg","",4,14,16);

  ifstream ifile("dati_highstat.dat");
  
  double mass;
  int    nobs=0;
  while (ifile >> mass){
    //calcolare nobs
    h->Fill(mass);
    if (mass>14 && mass<16){
      hreg->Fill(mass);
      nobs++;
    }
  }

  h->Draw();
  hreg->Draw("SAME");
  hreg->SetFillColor(2);

  cout << nobs << endl;
  
  //calcolare upper limit
  int ns = 0;
  while(1){
	  double prob=0;
	  for(int i = 0; i < nobs; i++){
		  prob += TMath::PoissonI( i, nbkg+ns);
	  }
	  if (prob < 0.05){
		  cout << "Upper limit al 95% di CL: " << ns-1  << endl;
		  break;
	  }
	  ns++;
  }
  
  
  app.Run(true);

}
