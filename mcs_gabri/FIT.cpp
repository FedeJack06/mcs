//**************//
//HANDS ON 2 E 3//
//**************//

//**********//
//HANDS ON 2//
//**********//

//************************************************************************************************************************//
//PROGRAMMA PER FIT SIMULTANEI                                                                                            //
//MINIMIZZAZIONE DELLA FUNZIONE chi2 DI CHI2 A PARTIRE DA DUE FUNZIONI F1 E F2 LINEARI NEI PARAMETRI CON PACCHETTO TMinuit//
//************************************************************************************************************************//

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>

using namespace std;

//Definizione del namespace dei dati
namespace data{
  int n;
  vector<double> x1,t1,et1;
  vector<double> x2,t2,et2;
}

//Istanziazione delle funzioni lineari nei parametri con cui eseguire il fit simultaneo
TF1 *f1;
TF1 *f2;

//Funzione di chi2 da minimizzare con TMinuit
void chi2(int &npar, double *gin, double &f, double *par, int iflag){
  f=0;
  f1->SetParameters(par[0],par[1],par[2],par[3]); //utilizza i seguenti parametri per f1 e f2  
  f2->SetParameters(par[0],par[1],par[4],par[5]);
  for(int i=0; i<data::n; i++){
    f+=pow((data::t1[i]-f1->Eval(data::x1[i]))/data::et1[i],2); //minimizzazione rispetto prima funzione
    f+=pow((data::t2[i]-f2->Eval(data::x2[i]))/data::et2[i],2); //minimizzazione rispetto prima funzione  
  }
}

//----//
//Main//
//---//
int main(){

  TApplication app("app",0,NULL);

  //Lettura file di dati e grafici
  ifstream fp1("perno1.dat"); 
  ifstream fp2("perno2.dat");
  double tx1,tt1,tex1,tet1; //si leggono posizioni e tempi con errori
  double tx2,tt2,tex2,tet2;

  TCanvas *c = new TCanvas();

  TGraphErrors gr1;
  while (fp1 >> tx1 >> tt1 >> tex1 >> tet1){
    data::x1.push_back(tx1);
    data::t1.push_back(tt1);
    data::et1.push_back(tet1);
    gr1.SetPoint(gr1.GetN(),tx1,tt1);
    gr1.SetPointError(gr1.GetN()-1,tex1,tet1);
  }

  TGraphErrors gr2;
  while (fp2 >> tx2 >> tt2 >> tex2 >> tet2){
    data::x2.push_back(tx2);
    data::t2.push_back(tt2);
    data::et2.push_back(tet2);
    gr2.SetPoint(gr2.GetN(),tx2,tt2);
    gr2.SetPointError(gr2.GetN()-1,tex2,tet2);
  }
  data::n=data::x1.size(); //numero di dati

  
  //Verifica dati abbiano andamento parabolico
  f1 = new TF1("f1","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);
  f2 = new TF1("f2","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);

  gr1.Fit("f1");
  gr2.Fit("f2");
  gr1.Draw("AP");
  gr2.Draw("P");
  app.Run(true);

  // Minuit per fit simultaneo
  TMinuit minuit(6);   //Si istanzia oggetto di TMinuit con numero parametri fit
  minuit.SetFCN(chi2); //Si setta la funzione da minimizzare
  //Si definiscono i parametri delle due funzioni
  minuit.DefineParameter(0,"x0",36,0.01,0,0);
  minuit.DefineParameter(1,"T0",4,0.01,0,0);
  minuit.DefineParameter(2,"a1",f1->GetParameter(2),0.01,0,0);
  minuit.DefineParameter(3,"b1",f1->GetParameter(3),0.01,0,0);
  minuit.DefineParameter(4,"a2",f2->GetParameter(2),0.01,0,0);
  minuit.DefineParameter(5,"b2",f2->GetParameter(3),0.01,0,0);

  //Comando di minimizzazione 
  minuit.Command("MIGRAD");

  //Presa dei risultati
  //Salvataggio parametri forniti dall'oggetto di TMinuit, ovvero la miglior stima dei parametri in gioco
  double x0,T0,a1,b1,a2,b2,ex0,eT0,ea1,eb1,ea2,eb2;
  minuit->GetParameter(0,x0,ex0);
  minuit->GetParameter(1,T0,eT0);
  //...
  cout << endl;
  cout << "x0 = " << x0 << "+/-" << ex0 << endl;
  cout << "T0 = " << T0 << "+/-" << eT0 << endl;
  //...

  //Grafici aggiornati
  f1->SetLineColor(kBlue);
  f2->SetLineColor(kBlue);
  f1->Draw("SAME");
  f2->Draw("SAME");
  c->Modified();
  c->Update();
  app.Run(true);

  return 0;
}
