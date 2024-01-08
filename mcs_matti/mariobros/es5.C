{//#include <cmath>
//#include <TCanvas.h>
//#include <TGraph.h>
//#include <TApplication.h>

double a(double x,double t,double m,double k,double A,double w){
  return (A*sin(w*t)-k*x)/m;
}

//using namespace std;

//int main(){
  //dati fisici del problema
  double m=1;
  double k=0.25;
  double A=0.1;
  double w=0.25;

  double x=1;
  double xsucc=0;
  double v=0;
  double vsucc=0;
  double dt = 0.1;

  double t=0;
  double tmax=100;
  double h=0.1;

  //grafico
  TGraph g;
  TCanvas c;
  //TApplication app("app",0,NULL);

  
  g.SetPoint(0,t,x);
  g.Draw();

  t = t + dt;

  int i=1;
  
  while(t<tmax){
    
    xsucc= x + h*v + (h*h*0.5)*a(x,t,m,k,A,w);
    vsucc= v + (h*0.5)*(a(xsucc,t,m,k,A,w) + a(x,t,m,k,A,w));

    x=xsucc;
    v=vsucc;

    g.SetPoint(i,t,x);

    c.Modified();
    c.Update();
    

    
    t=t+dt;
    i=i+1;
  }

  //app.Run(true);

  //return 0;
};
