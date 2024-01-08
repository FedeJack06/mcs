{
  ifstream ifile("daties8.dat");

  double x=0;
  double cov[3][3];

  TH1D *h=new TH1D("h","titolo",40,-1,1);

  while(ifile>>x){
    h->Fill(x);
  }
  h->Draw();

  TF1 *f=new TF1("f","[0]*(1+[1]*x+[2]*x*x)",0.,0.);
  f->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
  f->SetParameter(1,1);
  f->SetParameter(2,3);

  h->Fit("f","L");

  gMinuit->mnemat(&cov[0][0],3);

  double a=f->GetParameter(1);
  double ea=f->GetParError(1);
  double b=f->GetParameter(2);
  double eb=f->GetParError(2);

  cout<<"parametri "<<a<<"+/- "<<ea<<" /-----/ "<<b<<"+/-"<<eb<<" correlazione "<< cov[2][1]/(ea*eb)<<endl;
  cout<<"p-value "<<f->GetProb()<<endl;
}
