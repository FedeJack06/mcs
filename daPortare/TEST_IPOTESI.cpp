//////////////////////////////////////HANDS ON 9 - TEST HYPO
//////////////////////BASSA STATISTICA
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

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// P-VALUE ALTA STATISTICA

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

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// TEST HYPO PYTHON
from   sys   import *
from   math  import *
from   ROOT  import *
import numpy as np
from   scipy import stats


h1 = TH1D("h1","",40,0,0.5)
h2 = TH1D("h2","",40,0,0.5)

x1 = np.loadtxt("s1.dat")
x2 = np.loadtxt("s2.dat")
for i in range(len(x1)):
    h1.Fill(x1[i])
for i in range(len(x2)):
    h2.Fill(x2[i])

h1.SetLineColor(kRed)    
h2.SetLineColor(kBlue)
h1.Draw("E")
h2.Draw("ESAME")
gApplication.Run(True)

# test del chi2
print("Test chi1 (1/2) ", h1.Chi2Test(h2))#cambiando bin viene altro valore, ALTA VARIABILITÀ
print("Test chi2 (2/1) ", h2.Chi2Test(h1))

# test unbinned KS 2 campioni ##outuput statistica, pi-value
t_ks2, p_ks2 = stats.ks_2samp(x1, x2) #indip dal bin, dove utilizzabile (1D), più potente
print("test KS 2 samples ", p_ks2)

# test unbinned KS 1 pdf
#vuole una cumulativa
#expo con lamnda = 10
fun = stats.expon(loc=0.0, scale=0.1)
t_ks, p_ks = stats.kstest(x1, fun.cdf)
print("test KS (su s1)", p_ks)

#se 1 e 2 incompatibili, se faccio test sulla 2 il p-value dovrebbe venire incompatibile
t_ks, p_ks = stats.kstest(x2, fun.cdf)
print("test KS (su s2)", p_ks)

# test su esponenziale ignoto (con fit)
f = TF1("exp", "[0]/[1]*exp(-x/[1])")
f.SetParameter(1, 0.1)
f.SetParameter(2, h1.GetEntries()*h1.GetBinWidth(1))
h1.Fit("exp", "L")
chi2Newmann = h1.Chisquare(f, "N")
chi2BC = h1.Chisquare(f, "BC")
print("prob chi2N ", TMath.Prob(chi2Newmann, h1.GetNbinsX()-2))
print("prob chi2BC ", TMath.Prob(chi2BC, h1.GetNbinsX()-2))

gApplication.Run(True)
