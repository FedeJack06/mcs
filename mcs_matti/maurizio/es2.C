{
  TH1D *h=new TH1D("h","titolo",99,1,100);
  
  ifstream ifile("powerlaw.dat");
  double n_0,e;
  int i=1;
  while(ifile>>n_0>>e){
    h->SetBinContent(i,e);
    i++;
  }
  h->Draw();

  /*
  TF1 *f1=new TF1("f1","([0]*pow(x,(-[1])))",1,100);
  f1->SetParameter(0,232);
  f1->SetParameter(1,0.4);

  h->Fit("f1","L");

  cout<<"p-value solo potenza "<<f1->GetProb()<<endl;
  */
  
  //il p-value con solo potenza risulta basso rispetto all'accordo al 95%
  //rigettiamo l'ipotesi
  
  
  //matrice di covarianza per calcolo correlazione
  double cov[3][3];
  
  TF1 *f2=new TF1("f2","([0]*pow(x,(-[1])))*exp(-(x/[2]))",1,100);
  f2->SetParameter(0,232);
  f2->SetParameter(1,0.4);
  f2->SetParameter(2,10);

  h->Fit("f2","L");
  
  cout<<"p-value tutta la funzione "<<f2->GetProb()<<endl;
  
  /*
  //la matrice di covarianza restituisce correlazione moltiplicata per gli errori
  gMinuit->mnemat(&cov[0][0],3);
  double c= cov[1][2];
  double rho=c/(f2->GetParError(1)*f->GetParError(2));
  cout<<"correlazione gamma ecut "<< rho<<endl;
  */
}
