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
  
  app.Run(true);

}
