{
  ifstream infile("uv.dat");
  int index = 4;
  double v,ev,v_gen,tmp;
  TGraphErrors *gr = new TGraphErrors;
  int i = 0;
  double v_lin_start;
  while(infile >> v >> ev >> v_gen >> tmp){
    double eVgen = (v_gen*3e-4 + 5e-3)/pow(3, 0.5); //R=988 +- 2 ohm
    gr->SetPoint(i, v, v_gen);
    gr->SetPointError(i, ev, eVgen);
    i++;
    
    if (v_gen/988. < 5e-3) //soglia comune per calcolo fit lineare
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
  double lamb[5] = {624e-9, 467e-9, 590e-9, 520e-9, 405e-9};
  double freq = c/lamb[index];
  double efreq = (freq*10e-9)/lamb[index];
    
  //ofstream ofile("v_f_5mA.dat", std::ios_base::app);
  //ofile << x << " " << ex << " " << freq << " " << efreq << endl;
}
//uv 3, 4
//green 2.2, 4
//yellow 1.9, 4
//blue 2.5, 4
//red 1.75, 4   lambda 624e-9
