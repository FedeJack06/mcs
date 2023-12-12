{
  ifstream infile("v_f_5mA.dat");
  double vd, freq, evd, efreq;
  TGraphErrors *gr = new TGraphErrors;
  int i = 0;
  while(infile >> vd >> evd >> freq >> efreq){
    //if(v > 2.5){
      gr->SetPoint(i, vd, freq);
      gr->SetPointError(i, evd, efreq*0.9);
      i++;
      //}
  }
  gStyle->SetOptFit();
  gr->Draw("AP");
  TF1 *f1 = new TF1("f1","[0]+[1]*x", 0, 10);
  //f1->SetParameter(1, 2e14);
  //f1->SetParameter(0, 0);
  gr->Fit("f1");
  double m = f1->GetParameter(1);
  double q = f1->GetParameter(0);
  double x = -q/m;
  cout << "e/h fit " << m << " +- " << f1->GetParError(1) << endl;
  cout << "e/h " << 1.602e-19/6.626e-34 << endl;
  cout << "pi-value " << f1->GetProb() << endl;
}
