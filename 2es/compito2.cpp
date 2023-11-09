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
#include "Electron.h"
//#include "fb.h"
using namespace std;

  Vector3 fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
    // * ritorna la forza interna che il corpo j esercita su i
    return Vector3();
  }

Vector3 fExternal(unsigned int i, double t, vector<MatPoint> p, Vector3 CampoE, Vector3 CampoB){
    // * ritorna la forza esterna sul corpo i
    Vector3 fExt( p[i].Charge()*( CampoE + p[i].V().Cross(CampoB) ) );
    return fExt;
  }

int main() {
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  double x,y,z,vx,vy,vz;
  cout << "posizione iniziale eletrone: " << flush;
  cin >> x >> y >> x;
  cout << "velocità iniziale : " << flush;
  Vector3 p0(x,y,z), v0(vx, vy, vz);
  MatPoint e1(Electron e, p0, v0);
  
  vector<MatPoint> vectMat(0);
  vectMat.push_back(e1);

  OdeSolver ode("Rk4", vectMat);

  //imput E e B
  double Ex, Ey, Ez, Bx, By, Bz;
  cout << "componenti campo elettrico :" << flush;
  cin >> Ex >> Ey >> Ez;
  cout << "componenti campo magnetico :" <<flush;
  cin >> Bx >> By >> Bz;
  Vector3 E(Ex, Ey, Ez), B(Bx, By, Bz);

  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
  ode.fInternal = fInternal;
  ode.fExternal = fExternal;
  ode.DeltaT(0.5);

  
  //Creazione dei grafici (uno per pianeta)
  vector<TGraph> gr(ode.N());
  TCanvas c("c","",10,10,500,500);
  
  //Preparazione grafico delle coordinate dei pianeti
  double size=5; // 5 unita' astronimiche
  gPad->DrawFrame(-size,-size,size,size);
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,ode.GetMatPoint(i).R().X(),ode.GetMatPoint(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(1);
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();
  //app.Run(true);

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  while (ode.T()<3000){
    ode.Step();
    for (unsigned int i=0;i<ode.N();i++){
      //STEP 4 riempimento delle grafico gr[i] con le coordinate aggiornate dei pianeti
      gr[i].SetPoint(gr[i].GetN(), ode.GetMatPoint(i).R().X(), ode.GetMatPoint(i).R().Y());
      // * accedere al MatPoint i-esimo, al vettore di coordinate spaziali, alla coordinata voluta
      // * inserire nel grafico gr[i] le coordinate X e Y
      // N.B. L'indice del nuovo punto da inserire è pari al numero di punti già presente in ciascun grafico
    }
    gPad->Modified(); gPad->Update();
    gSystem->ProcessEvents();
  }

  app.Run(true);

  return 0;
}
