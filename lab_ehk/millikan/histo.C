{
  TTree *data = new TTree();
  data->ReadFile("millikan.dat", "t/D");

  TH1D *histo = new TH1D("histo", "Millikan exp", 60, 0, 10);
  //data->Draw("t >> *histo");
  ifstream input("millikan.dat");
  double tmp;
  while (input >> tmp)
    histo->Fill(tmp);
  histo->Draw();
  
  TF1 *f = new TF1("f", "[2]*TMath::Gaus(x, [0], [1]) + [3]*TMath::Gaus(x, 2*[0], [1]) + [4]*TMath::Gaus(x, 3*[0], [1])", 0, 6);
  f->SetParameters(1.6, 0.3, 0.3, 0.3, 0.3);
  //f->SetParLimits(1, 0, 1);
  //f->SetParLimits(2, 0, 1);
  //f->SetParLimits(3, 0, 1);
  //f->SetParLimits(4, 0, 1);
  //data->UnbinnedFit("f", "t", "t<6"); //unbinned
  histo->Fit("f", "LR"); //likehood extended in range

  //f->SetParameter(2, histo->GetEntries()*histo->GetBinWidth(1));
  //f->Draw("same");
  //moltiplico tutto per un parametro che fisso a 1 e poi moltiplico all'area del istogramma
}
