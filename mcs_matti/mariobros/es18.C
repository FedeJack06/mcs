{
  int N=100000;
  TRandom3 rnd;
  rnd.SetSeed(123456789);

  ofstream ofile("nome.dat");

  TH1D *h=new TH1D("h","titolo",40,0.,0.);

  double x=0;
  for(int i=0;i<N;i++){
    x=pow(rnd.Rndm(),(1./3.));
    ofile<<x<<endl;
    h->Fill(x);
  }
  h->Draw();
  TTree *t=new TTree();

  t->ReadFile("nome.dat","t/D");

  TF1 *f=new TF1("f","[0]*[1]*pow(x,[1]-1)",0,1);

  f->FixParameter(0,1);
  f->SetParameter(1,3);
  
  t->UnbinnedFit("f","t");
  f->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));

  f->Draw("SAME");

  cout<<"p-value "<<f->GetProb()<<endl;
    

}
