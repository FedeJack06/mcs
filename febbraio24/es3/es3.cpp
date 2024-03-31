#include <cmath>
#include <iostream>
#include <vector>

#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TSystem.h>

#include "OdeSolver.h"
#include "Vector3.h"
#include "MatPoint.h"
/*
particella con m = 1 Gev (c=1 quindi m = 1 kg), si muove lungo asse y con vi = 0.1c
campo B = (B0 + aplha*x) lungo z per x>=0 , aplha = 1 T/m
Tracciare nel grafico xy la traiettoria fino a 2 Periodi
*/
using namespace std;

  Vector3 fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
    // * ritorna la forza interna che il corpo j esercita su i
    return Vector3();
  }

Vector3 fExternal(unsigned int i, double t, vector<MatPoint> p){
    // * ritorna la forza esterna sul corpo i
    Vector3 fExt;
    if (p[i].R().X() >= 0){
      Vector3 B(0,0,0.2+p[i].R().X());
      fExt = Vector3( p[i].Charge()*(p[i].V().Cross(B) ) );
      return fExt;
    }
    else
      fExt = Vector3(0,0,0);
      return fExt;
  }

int main() {
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  Vector3 p0(0,1,0), v0(0, -0.1, 0);
  MatPoint e1(1, 1, p0, v0);
  
  vector<MatPoint> vectMat(0);
  vectMat.push_back(e1);

  OdeSolver ode("Rk2", vectMat);

  ode.fInternal = fInternal;
  ode.fExternal = fExternal;
  ode.DeltaT(0.5);

  vector<TGraph> gr(ode.N());
  TCanvas c("c","",10,10,500,500);
  
  //Preparazione grafico delle coordinate dela particella
  double size=100; 
  gPad->DrawFrame(-size,-size,size,size);
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,ode.GetMatPoint(i).R().X(),ode.GetMatPoint(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(1);
    gr[i].GetXaxis()->SetTitle("x [m]");
    gr[i].GetYaxis()->SetTitle("y [m]");
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();

  while (ode.T()<300){
    ode.Step();
    for (unsigned int i=0;i<ode.N();i++){
      gr[i].SetPoint(gr[i].GetN(), ode.GetMatPoint(i).R().X(), ode.GetMatPoint(i).R().Y());
    }
    gPad->Modified(); gPad->Update();
    gSystem->ProcessEvents();
  }

  app.Run(true);

  return 0;
}
