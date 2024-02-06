#include <cmath>
#include <iostream>
#include <vector>

#include <TGraph2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TSystem.h>

#include "OdeSolver.h"
#include "Vector3.h"
#include "MatPoint.h"
#include "Electron.h"
#include "fb.h"
using namespace std;

Vector3 fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
  // * ritorna la forza interna che il corpo j esercita su i
  return Vector3();
}

Vector3 fExternal(unsigned int i, double t, vector<MatPoint> p){
  // * ritorna la forza esterna sul corpo i
  Vector3 CampoE(0,0,0);
  Vector3 CampoB( CampoBottiglia(p[i].R()) );
  //Vector3 CampoB(0,0,1e-5);
  Vector3 fExt( p[i].Charge()*( CampoE + p[i].V().Cross(CampoB) ) );
  return fExt;
}

int main() {
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  double x,y,z,vx,vy,vz;
  cout << "posizione iniziale eletrone x y z: " << flush;
  cin >> x >> y >> z;
  cout << "velocità iniziale vx vy vz: " << flush;
  cin >> vx >> vy >> vz;
  Vector3 p0(x,y,z), v0(vx, vy, vz);

  Electron e1;
  MatPoint p1(e1, p0, v0);
  
  vector<MatPoint> vectMat(0);
  vectMat.push_back(p1);

  OdeSolver ode("Rk4", vectMat);

  ode.fInternal = fInternal;
  ode.fExternal = fExternal;
  ode.DeltaT(1e-9);
  
  //Vector di TGraph
  vector<TGraph2D> gr(ode.N());
  TCanvas c("c","",10,10,1000,1000);
  
  //Canvas + condizioni iniziali
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0, ode.GetMatPoint(i).R().X(), ode.GetMatPoint(i).R().Y(), ode.GetMatPoint(i).R().Z());
    gr[i].SetMarkerColor(color[i]);
    gr[i].SetMarkerStyle(20);
    gr[i].SetMarkerSize(0.5);
    gr[i].GetXaxis()->SetTitle("X");
    gr[i].GetYaxis()->SetTitle("Y");
    gr[i].GetZaxis()->SetTitle("Z");
  }
  
  //Run del metodo numerico + grafico
  while (ode.T()<1e-5){
    ode.Step();
    for (unsigned int i=0;i<ode.N();i++){
      gr[i].SetPoint(gr[i].GetN(), ode.GetMatPoint(i).R().X(), ode.GetMatPoint(i).R().Y(), ode.GetMatPoint(i).R().Z());
      // N.B. L'indice del nuovo punto da inserire è pari al numero di punti già presente
    }
  }
  
  for (unsigned int i=0;i<ode.N();i++)
    gr[i].Draw("P");

  app.Run(true);

  return 0;
}
