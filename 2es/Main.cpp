#include <cmath>
#include <fstream>
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

using namespace std;

Vector3 fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){ //i soggetto a forza gen da j
  //STEP 2 definizione forza interna
  // * ritorna la forza interna che il corpo j esercita su i
  Vector3 forza_int(p[j].GravField( p[i].R() ) * p[i].Mass());
  return forza_int;
}

Vector3 fExternal(unsigned int i, double t, vector<MatPoint> p){
  //STEP 2 definizione forza esterna
  // * ritorna la forza esterna sul corpo i
  return Vector3();
}

int main(){
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  //Lettura dei dati dal file
  double mass;
  double x,y,z,vx,vy,vz;
  ifstream f("fileInput");

  vector<MatPoint> vectMat(0);
  OdeSolver ode("Rk4", vectMat);
  
  // STEP 1 - opzione 1
  // * Creazione OdeSolver vuoto (senza passare vector<MatPoint>);
  // * Assegnazione dei MatPoint con il metodo AddMatPoint
  // STEP 1 - opzione 2
  // * Creazione e riempimento vector<MatPoint>
  // * Creazione di OdeSolver passando vector<MatPoint>
  while (f >> mass >> vx >> x >> vy >> y >> vz >> z){
    MatPoint temp(mass, 0, Vector3(x, y, z), Vector3(vx, vy, vz));
    ode.AddMatPoint(temp);
  }

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
