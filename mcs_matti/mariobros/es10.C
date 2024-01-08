double M=0;
double G=0;

TVector2 a(TVector2 r){
  TVector2 a;
  a.SetX(-(G*M/pow(r.Mod(),3))*r.X());
  a.SetY(-(G*M/pow(r.Mod(),3))*r.Y());
  return a;
}

void es10(){
  M=100;
  //M=2e30;
  G=1;
  //G=6.67e-11;
  TVector2 r;
  TVector2 rsucc;
  TVector2 v;
  TVector2 vsucc;
  double t=0;
  double dt=0.01;
  double tend=1000;
  
  TGraph g;
  TCanvas c;

  //r.SetX(147.0994e09);
  //v.SetY(30.2865e03);
  r.SetX(50);
  v.SetY(1.5);
  g.SetPoint(0,r.X(),r.Y());
  g.Draw();

  int i=1;
  while(t<tend){
    rsucc= r + v*dt;
    vsucc= v + a(rsucc)*dt;

    c.Modified();
    c.Update();
    g.SetPoint(i,rsucc.X(),rsucc.Y());
    
    r=rsucc;
    v=vsucc;
    t=t+dt;
    i++;
  }

}
