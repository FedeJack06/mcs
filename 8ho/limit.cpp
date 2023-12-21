#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TH1D.h>
#include <TMath.h>

using namespace std;

int main(){

  double nbkg = 22.35; 

  TApplication app("app",NULL,NULL);

  TH1D *h = new TH1D("h","",40,0,40);
  TH1D *hreg = new TH1D("hreg","",2,14,16);

  ifstream ifile("dati_lowstat.dat");
  
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

  //calcolare p-value Ns=0
  double prob=0;
  
  app.Run(true);

}
