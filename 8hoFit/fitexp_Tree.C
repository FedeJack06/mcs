namespace data{
  vector<double>  x;
}

void logl(int &npar, double *gin, double &f, double *par, int iflag){
  f = 0.0;
  // Definisco la logl, log(L)
  for(int i=0; i< data::x.size(); i++){
    f += log(par[0]) + data::x[i]/par[0];
  }
  
}

void fitexp_Tree(){

  ifstream file("exp.dat");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    h->Fill(x);
  }
  TTree *t = new TTree();
  t->ReadFile("exp.dat", "t/D");
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  fe->FixParameter(0, 1.);
  fe->SetParameter(1, 2.);
  t->UnbinnedFit("fe", "t");

  h->SetMarkerStyle(20);
  h->Draw("E");
  // Disegno della funzione
  //cambiare la normalizzazione altrimenti incoerenti con l'istogramma
  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(1));
  fe->Draw("same");
}

