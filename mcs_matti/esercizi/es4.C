//altro modo di farlo senza usare tminuit ma solo likelihood
//non funziona, in questo caso andava meglio l'altro
{
  TH1D *h=new TH1D("h","",25,0.,0.);

  ifstream ifile("DatiGamma.dat");
  
  double a;
  while(ifile>>x){
    h->Fill(a);
  }

  h->Draw();

  TF1 *f=new TF1("f","[1]*((pow(x,2)*exp(-x/[0]))/(2*pow([0],3)))",0,30);
  f->FixParameter(1,224);
  f->FixParameter(0,pow(5.74,1/3));
  
  f->SetParameter(1,h->GetBinWidth(1)*h->GetEntries());
  
  h->Fit("f","L");


  cout<<f->GetParameter(0)<<endl;

}
