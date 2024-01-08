
double b;
double g;
double h;

double a(double v,double z){
  double a=-(1/z)*(pow(v,2) + b*v + g*(z-h));
  return a;
}

void es1(){
  //condizioni fisiche
  b=0.25;
  g=9.81;
  h=0.1;
  

  //tempo totale e alla precisione
  double t=0;
  double tend=10000;
  double dt=0.01;
  double p=0.01;

  double z;
  double zsucc;
  double v;
  double vsucc;
  double k1,w1,k2,w2;

  TCanvas *c=new TCanvas;
  TCanvas *c1=new TCanvas;
  TCanvas *c2=new TCanvas;
  TGraph *gr=new TGraph;
  TGraph *gr1=new TGraph;
  TGraph *gr2=new TGraph;
  
  
  //punto iniziale
  c->cd();
  z=0.01;
  v=0;
  gr->SetPoint(0,t,z);
  gr->Draw();
  
  c1->cd();
  gr1->SetPoint(0,t,v);
  gr1->Draw();
  
  c2->cd();
  gr2->SetPoint(0,t,a(v,z));
  gr2->Draw();

  int i=1;  
  while (t<tend){

    //RK2
    
    k1=p*v;
    w1=p*a(v,z);
    
    k2=p*(v+k1/2);
    w2=p*a(v+(w1/2),z);
    
    zsucc=z+k2;
    vsucc=v+w2;
    
    
    if((abs(zsucc-h))<(0.01*h)){
      break;
    }
    
    
    c->cd();
    c->Modified();
    c->Update();
    gr->SetPoint(i,t,zsucc);

    c1->cd();
    c1->Modified();
    c1->Update();
    gr1->SetPoint(i,t,vsucc);

    c2->cd();
    c2->Modified();
    c2->Update();
    gr2->SetPoint(i,t,a(v,z));
    
    z=zsucc;
    v=vsucc;
    t=t+dt;
    i=i+1;
  }
}
