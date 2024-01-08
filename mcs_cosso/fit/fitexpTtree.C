void fitexpTtree(){

  ifstream file("exp.dat");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    h->Fill(x);
  }

  TTree *tree = new TTree();
  tree->ReadFile("exp.dat", "tree/D"); //gli do nome del file di dati e nome della variabile
  h->SetMarkerStyle(20);
  h->Draw("E");
  
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  // Disegno della funzione
  fe->SetParameter(1, 2.0);
  fe->FixParameter(0, 1); //lo fisso cosi che lui non tenti di fittarlo, ma semplicemtne lo fisso cisi che poi il fit venga fatto da TTree
  tree->UnbinnedFit("fe" , "tree");

  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(1));
  fe->Draw("SAME");
}
