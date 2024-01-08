//**********//
//HANDS ON 4//
//**********//

//***************************************************************************************************//
//PROGRAMMA 1: RIGETTO O MENO DI UNA IPOTESI NULLA DI CONTEGGI CON CALCOLO p-value DI UNA POISSONIANA//
//***************************************************************************************************//

#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TH1D.h>
#include <TMath.h>

using namespace std;

int main(){

  //Numero eventi di fondo attesi
  double nbkg = 22.35; 

  TApplication app("app",NULL,NULL);

  //Istanziazione istogrammi, allocazione dinamica
  TH1D *h = new TH1D("h","",40,0,40);
  TH1D *hreg = new TH1D("hreg","",2,14,16);

  ifstream ifile("dati_lowstat.dat");

  //Calcolo eventi osservati nell'intervallo di interesse
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
  cout << "Nobs = " << nobs << endl;
  h->Draw();
  hreg->Draw("SAME");
  hreg->SetFillColor(2);

  //Si calcola la probabilita' di avere piu' eventi di quelli osservati data ipotesi nulla con numero eventi di fondo
  //Si calcola il p-value di una Poissoniana centrata in nbgk supponendo eventi significativi Ns=0
  //Si risolve in modo complementare: non si somma da nobs a +inf, ma da 1 a nobs
  double prob=0;
  for(int i=0; i<nobs; i++){
    prob+=TMath::PoissonI(i,nbkg);//PoissonI poissoniana binnata: i eventi osservati, nbgk eventi attesi
  }

  if(1-prob>0.5){
    cout<<"Ipotesi nulla NON rigettabile"<<endl; 
    cout<<"p-value "<<1-prob<<endl;
  }
  else{
    cout<<"Ipotesi nulla rigettabile"<<endl; 
    cout<<"p-value "<<1-prob<<endl; 
  }
  
  app.Run(true);

}

//***********************************************************************************************************************************************//
//PROGRAMMA 2: CALCOLARE AL 95% DI CL IL LIMITE SUPERIORE ED INFERIORE AL NUMERO DI EVENTI DI SEGNALE TALE CHE L'IPOTESI ZERO NON SIA RIGETTABILE//
//***********************************************************************************************************************************************//

#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TH1D.h>
#include <TMath.h>

using namespace std;

int main(){
  //Numero eventi di fondo attesi
  double nbkg = 44.7; 

  TApplication app("app",NULL,NULL);

  //Istanziazione istogrammi, allocazione dinamica
  TH1D *h = new TH1D("h","",80,0,40);
  TH1D *hreg = new TH1D("hreg","",4,14,16);

  ifstream ifile("dati_highstat.dat");

  //Calcolo eventi osservati nell'intervallo di interesse
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
  cout << "nobs=" << nobs << endl;
  h->Draw();
  hreg->Draw("SAME");
  hreg->SetFillColor(2);

  //Si calcola il limite superiore: scelta ns arbitraria
  for(int ns=0;ns<1000;ns++){
    double prob=0;
    for(int i=0;i<=nobs;i++){
      prob += TMath::PoissonI(i,ns+nbkg);
    }
    if(prob<0.025){
      cout << "Upper Limit 95% confidence level" << ns << endl;
      break;
    }
  }

  //Si calcola il limite inferioree: scelta ns arbitraria
  for(int ns=0;ns<1000;ns++){
    double prob=0;
    for(int i=0;i<=nobs;i++){
      prob += TMath::PoissonI(i,ns+nbkg);
    }
    if((1-prob)>=0.025){
      cout << "Lower Limit 95% confidence level" << ns << endl;
      break;
    }
  }
     
     
  
  app.Run(true);

}

