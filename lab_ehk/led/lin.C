{
  ifstream infile("3mA");
  double vd, freq, evd, efreq;
  TGraphErrors *gr = new TGraphErrors;
  int i = 0;
  while(infile >> vd >> evd >> freq >> efreq){
    //if(v > 2.5){
      gr->SetPoint(i, vd, freq);
      gr->SetPointError(i, evd, efreq*0.8);
      i++;
      //}
  }
  gStyle->SetOptFit();
  gr->SetTitle("Frequenza LED vs Tensione di soglia");
  gr->GetXaxis()->SetTitle("Tensione di soglia [V]");
  gr->GetYaxis()->SetTitle("Frequenza emessa [Hz]");
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
//e/h fit 2.37399e+14 +- 8.97135e+12 con errori *1.5 soglia 5mA = (2.37 +- 9)e14
//e/h fit 2.42456e+14 +- 4.88142e+12 con errori *0.8 soglia 3mA = (2.42 +- 5)e14
//media pesata e/h = (2.41 +- 0.04)e14
