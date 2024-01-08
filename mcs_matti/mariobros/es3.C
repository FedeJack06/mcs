{
  ifstream ifile("Dati_Spettrometro.dat");

  TH1D *h=new TH1D("h","titolo",60,0.555,0.593);
 
  double d=0;
  while (ifile>>d){
    h->Fill(d);
  }

  h->Draw();

  //singola gaussiana
  /*
  TF1 *f=new TF1("f","[0]*TMath::Gaus(x,[1],[2],1)",0.,0.);

  f->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
  f->SetParameter(1,h->GetMean());
  f->SetParameter(2,h->GetRMS());
  h->Fit("f","L");
  


  cout<<"p-value singola gaussiana "<<f->GetProb()<<endl;

  */
  //singola gaussiana non va bene, metto due gaussiana
  TF1 *f1=new TF1("f1","[0]*([1]*TMath::Gaus(x,[2],[3],1) + (1-[1])*TMath::Gaus(x,[4],[5],1))",0.,0.);
  
  f1->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
  f1->SetParameter(2,0.57);
  f1->SetParameter(3,0.0001);
  f1->SetParameter(4,0.585);
  f1->SetParameter(5,0.0004);
  h->Fit("f1","L");

  cout<<"p-value con due gaussiane "<<f1->GetProb()<<endl;
}
