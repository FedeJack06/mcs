#include <cmath>
#include <iostream>
#include "TVector2.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"

TVector2 acc(TVector2 r,double M){
  TVector2 acc;
  acc.SetX(-(M/pow(r.Mod(),3))*r.X());
  acc.SetY(-(M/pow(r.Mod(),3))*r.Y());

  //acc=(M/pow(r.Mod(),3))*r;
  return acc;
}


int main(){

  TVector2 r;
  TVector2 rsucc;
  TVector2 v;
  TVector2 vsucc;
  TVector2 a;
  
  double M=1.989e30;
  double x0=152.1e09;
  double v0=30e03;

  double t=0;
  double tend=100;
  double dt=0.01;

  TApplication app("app",0,NULL);
  TGraph gr;
  TCanvas c;

  //condizioni iniziali
  r.SetX(x0);
  v.SetY(v0);
  gr.SetPoint(0,r.X(),r.Y());
  gr.Draw();

  t=t+dt;
  int i=1;
  while(t<tend){

    rsucc = r + v*dt;
    vsucc = v + acc(r,M)*dt;
    std::cout<<" "<<r.X()<<" "<<acc(r,M).X()<<std::endl;

    r=rsucc;
    v=vsucc;
    
    c.Modified();
    c.Update();
    gr.SetPoint(i,r.X(),r.Y());
    
    t=t+dt;
    i++;
  }
  
  app.Run(true);  

}
