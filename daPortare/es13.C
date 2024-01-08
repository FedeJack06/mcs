{

  double x1=1;
  double s1=0.1/sqrt(3);
  double x2=2;
  double s2=0.1/sqrt(3);
    
    //grafico dell'errore

  TF1 f("f","sqrt([0]**2+[1]**2-1*2*x*[0]*[1])",-1,1);
  f.FixParameter(0,s1);
  f.FixParameter(1,s2);
  f.Draw();

  cout<<x1-x2<<" " <<f.Eval(1)<<endl;
  }
