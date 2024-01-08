#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TH1D.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraph.h>
using namespace std;

//file con dati da 0 a 40 a bassa statistica
//eventi di fondo noti seguono distr Poisson centrata in 22.35
//teoria prevede roba interessante tra 14 e 16
//in [14,16] ho eventi di fondo (H0) oppure eventi nuovi(H1)?
//calcolo probabilità che n^ eventi in [14,16] siano fluttuazioni della distribuzione di fondo aspettato: 22.35 fluttua fino a Nobs (mis tra 14 e 16)?
int main(){ //vedi slide esTestHypo.pdf

  double nbkg = 22.35;//n^ eventi di fondo atteso, centro della Poissoniana

  TApplication app("app",NULL,NULL);

  TH1D *h = new TH1D("h","",40,0,40);
  TH1D *hreg = new TH1D("hreg","",2,14,16);

  ifstream ifile("dati_lowstat.dat");
  
  double mass;
  int    nobs=0; //n^ eventi osservati tra [14, 16]
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

  //calcolare p-value
  double prob=0;//prob ottenere i<nobs eventi, secondo distr Poisson
  for (int i=0; i<nobs; i++){
    prob += TMath::PoissonI(i,nbkg);//cumulativa della poissoniana
  }
  cout << 1-prob << endl;//pi value non è sempre 1-prob, a volte gia prob, dipende come integro
  cout << "nobs " << nobs << endl;

  //disegno distribuzione poisson centrata in Nbkg (non serve per l'es)
  TH1D *poisson = new TH1D("poisson", "Poisson(n,Nb)", 50, 0, 50);
  //TGraph *gr = new TGraph();
  for (int i=0; i<50; i++)
    //gr->SetPoint(i, i, TMath::PoissonI(i, nbkg));
    poisson->SetBinContent(i, TMath::Poisson(i, nbkg));
  TCanvas *can = new TCanvas("c2","c2", 1000, 700);
  can->cd();
  poisson->Draw();
  //gr->Draw("AL");
  
  app.Run(true);
  //o rigetto l'ipotesi o non la rigetto (non è che accetto H0)

  //qui rigetto H0 perchè p < alpha(5% o 1%), Nobs=36 non fa parte del fondo ma è un nuovo fenomeno interessante
}
