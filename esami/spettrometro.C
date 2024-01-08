{
  ifstream ifile("Dati_Spettrometro.dat");
  double tmp;
  TH1D *histo = new TH1D("histo", "", 70, 0.555, 0.595);
  while(ifile >> tmp){
    histo->Fill(tmp);
  }
  histo->Draw();
  /*
  TF1 *gaus = new TF1("gaus", "[0]*TMath::Gaus(x,[1],[2])");
  gaus->SetParameter(0, histo->GetEntries()*histo->GetBinWidth(1));
  gaus->SetParameter(1, histo->GetMean());
  gaus->SetParameter(2, histo->GetRMS());
  histo->Fit("gaus", "L");//uso likehood perchè ho bin con freq < 5, no chi^2
  cout<<"p-value "<< gaus->GetProb() << endl;//valore < 0.05, rigetto gauss singola
  */
  TF1 *gaus2 = new TF1("gaus2", "[0]*([1]*TMath::Gaus(x,[2],[3]) +(1-[1])*TMath::Gaus(x, [4],[5]))");
  gaus2->SetParameter(0, histo->GetEntries()*histo->GetBinWidth(1));
  gaus2->SetParameter(2, 0.57);
  gaus2->SetParameter(3, 0.0001);
  gaus2->SetParameter(4, 0.582);
  gaus2->SetParameter(5, 0.0001);
  histo->Fit("gaus2", "L");
  cout<<"p-value "<< gaus2->GetProb() << endl;

  //calcolo A dalle due gaussiane
  double B=0.1, V=1e3; q=TMath::Qe();
  
  double d1 = gaus2->GetParameter(2);
  double m1 = (B*B*q/(2*V))*pow(d1/2, 2);
  double A1 = m1/1.66e-27;
  cout << "m1 :" << A1 << endl;

  double d2 = gaus2->GetParameter(4);
  double m2 = (B*B*q/(2*V))*pow(d2/2, 2);
  double A2 = m2/1.66e-27;
  cout << "m2 :" << A2 << endl;
}
