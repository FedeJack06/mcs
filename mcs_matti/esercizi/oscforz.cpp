#include <cmath>
#include <vector>

#include <TGraph.h>
#include <TCanvas.h>
#include <TApplication.h>

using namespace std;

double a(double x,double t,double A,double w,double k,double mass){
  //con forzante Asin(wt)
  return (A*sin(w*t)-k*x)/mass;
  //senza forzante
  // return (-k*x)/mass;
}

int main(){
  //condizioni fisiche
  double k=0.25;
  double mass=1;
  double A=0.1;
  double w=0.25;
  double h=0.1;
  double t=0;
  double tend=100;
  double dt=0.1;

  double x=0;
  double xsucc=0;
  double v=0;
  double vsucc=0;

  TApplication app("app",0,NULL);
  TCanvas c;
  TGraph gr;

  //punto iniziale
  x=1;
  gr.SetPoint(0,t,x);
  gr.Draw();
  
  //iterazione
  int i=1;
  while (t<tend){
    xsucc = x + h*v + (pow(h,2)/2)*a(x,t,A,w,k,mass);
    vsucc = v + (h/2)*(a(xsucc,t+dt,A,w,k,mass) + a(x,t,A,w,k,mass));

    c.Modified();
    c.Update();
    gr.SetPoint(i,t,xsucc);
    
    x=xsucc;
    v=vsucc;
    t=t+dt;
    i=i+1;
  }

  app.Run(true);
}
