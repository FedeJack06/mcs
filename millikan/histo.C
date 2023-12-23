{
  /*ifstream in("millikan.dat"); NO CHI QUADRO PERCHE ERRORI NON DISTRIBUITI COME GAUSS PERCHE POCHI DATIX
    TH1D *histo = new TH1D("histo", "millikan", 60, 0, 7);
    double tmp;
    while(in >> tmp)
    histo->Fill(tmp);

    histo->Draw();
    //TF1 *gauss = new TF1("gauss", "[2]*exp(-0.5*pow((x-[1])/[0], 2)) + [2]*exp(-0.5*pow((x-2*[1])/[0], 2)) + [2]*exp(-0.5*pow((x-3*[1])/[0], 2))", 0, 7);
    TF1 *gauss = new TF1("gauss", "[2]*TMath::Gaus(x, [0], [1], 1) + [3]*TMath::Gaus(x, 2*[0], [1], 1) + [4]*TMath::Gaus(x, 3*[0], [1], 1)", 0, 7);
    gauss->SetParameters(1.6, 0.3, 0.3, 0.3, 0.3);

    histo->Fit("gauss");*/

  TTree *data = new TTree();
  data->ReadFile("millikan.dat", "t/D");
  TH1D *histo = new TH1D("histo", "Millikan exp", 50, 0, 7);
  data->Draw("t >> *histo");

  TF1 *f = new TF1("f", "[2]*TMath::Gaus(x, [0], [1]) + [3]*TMath::Gaus(x, 2*[0], [1]) + [4]*TMath::Gaus(x, 3*[0], [1])", 0, 6);
  f->SetParameters(1.6, 0.3, 0.3, 0.3);
  f->SetParLimits(0, 1.5, 1.7);
  f->SetParLimits(1, 0, 3);
  f->SetParLimits(2, 0, 3);
  f->SetParLimits(3, 0, 2);
  data->UnbinnedFit("f", "t");
  f->Draw("same");
  //moltiplico tutto per un parametro che fisso a 1 e poi moltiplico all'area del istogramma
}
