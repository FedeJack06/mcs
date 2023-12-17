{
  //0 IR// 1 RED// 2 YELLOW// 3 GREEN// 4 BLUE// 5 UV //INDEX
  ifstream infile("uv.dat");
  int index = 5;
  double v,ev,v_gen,tmp;
  TGraphErrors *gr = new TGraphErrors;
  int i = 0;
  double v_lin_start;
  while(infile >> v >> ev >> v_gen >> tmp){
    double eVgen = (v_gen*3e-4 + 5e-3)/pow(3, 0.5); //R=988 +- 2 ohm
    gr->SetPoint(i, v, v_gen);
    gr->SetPointError(i, ev, eVgen);
    i++;
    
    if (v_gen/988. < 3e-3) //soglia comune per calcolo fit lineare
      v_lin_start = v;
  }
  gr->Draw("AP");

  TF1 *f1 = new TF1("f1","[0]+[1]*x", v_lin_start, 4);
  gr->Fit("f1","R");
  double m = f1->GetParameter(1);
  double q = f1->GetParameter(0);
  double em = f1->GetParError(1);
  double eq = f1->GetParError(0);
  double x = -q/m; //intercetta asse x della retta
  double ex = x*pow(pow(em/m, 2) + pow(eq/q, 2), 0.5);
  cout << "v (i<5mA) " << v_lin_start << endl;
  cout << "v': " << x << " +- " << ex << " V" << endl;

  double c = 299792458;
  double lamb[6] = {883e-9, 633e-9, 589e-9, 534e-9, 473e-9, 382e-9};
  double eLamb[6] = {12e-9, 9e-9, 6e-9, 13e-9, 13e-9, 6e-9};
  double freq = c/lamb[index];
  double efreq = (freq*eLamb[index])/lamb[index];
    
  ofstream ofile("3mA_v_f.dat", std::ios_base::app);
  ofile << x << " " << ex << " " << freq << " " << efreq << endl;
}
