void dati_spettrometro(){
  TH1D *h= new TH1D("h","spettrometro",80,0.55,0.59);
  ifstream ifile("Dati_Spettrometro.dat");

  double d;
  while(ifile>>d){
    h->Fill(d);
  }

  h->Draw();
  
  TF1 *g= new TF1("g","[0]*TMath::Gaus(x,[1],[2],1)",0.55,0.59);
  g->FixParameter(0,1);
  g->SetParameter(1,h->GetMean());
  g->SetParameter(2,h->GetRMS());

  g->SetParameter(0,h->GetBinWidth(1)*h->GetEntries());


  h->Fit("g","L");


  //g->Draw("SAME");
  std::cout<< g->GetProb()<<std::endl;
  
}
