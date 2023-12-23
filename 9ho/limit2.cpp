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

  //calcolare upper limit
  double prob=0;
  //eveti osservati
  cout << "Nobs :" << nobs <<endl;
  //limite (dopo aver visto nobs 94) => valor medio +- è 
  int NsMax = 100;
  for(int ns = 0; ns<NsMax; ns++){//ns>=0; ns-- lower limit oppure ns<NsMax; ns++, int ns= altro val grande
    prob = 0.0;
    for (int i=0; i<=nobs; i++){
      prob += TMath::Poisson(i, nbkg+ns);
    }
    if (prob < 0.05){//upper limit //1 - prob < 0.05 è lower limit
      cout << "upper limit " << ns << endl;
      break;
    }
  }
  
  app.Run(true);

}
