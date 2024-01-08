//qauntità misurate
double eh[4]   = {2.39, 2.41, 2.44, 2.38};//e14
double e_eh[4] = {0.06, 0.04, 0.06, 0.05};
double ek[3]   = {1.11610, 1.15825, 1.13567};//e4
double e_ek[3] = {0.00031, 0.00132, 0.00018};
double hk[6]   = {3.34, 4.00, 3.81, 4.18, 3.33, 5.77};//e-11
double e_hk[6] = {0.09, 0.16, 0.09, 0.06, 0.14, 0.19};
double e = 1.626;//e-19
double e_e = 0.023;

void fcn(int &npar,double *gin,double &f,double *par,int iflag){
  f = 0.0;
  // Calcolo del Chi2
  for (int i=0; i<4; i++)
    f += pow((eh[i]*1e14 - par[0]/par[1])/(e_eh[i]*1e14), 2);
  for (int i=0; i<3; i++)
    f += pow((ek[i]*1e4 - par[0]/par[2])/(e_ek[i]*1e4), 2);
  for (int i=0; i<6; i++)
    f += pow((hk[i]*1e-11 - par[1]/par[2])/(e_hk[i]*1e-11), 2);
  f += pow((e*1e-19 - par[0])/(e_e*1e-19), 2);
}

void ehk(){
  // Define the minimization problem
  TMinuit *minuit = new TMinuit(3); // numero di parametri
  minuit->SetFCN(fcn);
  minuit->DefineParameter(0,"e", 1.5e-19, 0.01, 1e-19, 2e-19);
  minuit->DefineParameter(1,"h", 6.5e-34, 0.01, 3e-34, 8e-34);
  minuit->DefineParameter(2,"k", 1.3e-23, 0.01, 1e-23, 2e-23);
  //per ogni parametro inserisco nome, valore iniziale, step, minimo, massimo

  minuit->Command("MIGRAD"); // Comando di minimizzazione
  //HESSE calcolo preciso matrice di covarianza ed errori
  //MINOS calcolo erorrori asim
  minuit->Command("MINOS");

  //Get result
  double E, H, K, eE, eH, eK;
  minuit->GetParameter(0,E,eE);
  minuit->GetParameter(1,H,eH);
  minuit->GetParameter(2,K,eK);

  //Contour
  minuit->SetErrorDef(2.3);//for n-sigma contour -> SetErrorDef(n^2) 
  auto *c = new TCanvas("contour", "Contour", 1920, 1080);
  c->Divide(3, 1);
  
  c->cd(1);
  auto *con = (TGraph*)minuit->Contour(100, 0, 1);
  con->SetTitle("e vs h");
  con->GetXaxis()->SetTitle("e [C]");
  con->GetYaxis()->SetTitle("h [Js]");
  con->SetFillColor(kYellow-10);
  //minuit->SetErrorDef(1);
  //auto *con23 = (TGraph*)minuit->Contour(100,0,1);
  //con23->SetLineColor(kRed);
  con->Draw("ALf");
  //con23->Draw("L");
  
  c->cd(2);
  auto *con1 = (TGraph*)minuit->Contour(100, 0, 2);
  con1->SetTitle("e vs k");
  con1->GetXaxis()->SetTitle("e [C]");
  con1->GetYaxis()->SetTitle("k [J/K]");
  con1->SetFillColor(kBlue-10);
  con1->Draw("ALf");

  c->cd(3);
  auto *con2 = (TGraph*)minuit->Contour(100, 1, 2);
  con2->SetTitle("h vs k");
  con2->GetXaxis()->SetTitle("h [Js]");
  con2->GetYaxis()->SetTitle("k [J/K]");
  con2->SetFillColor(kRed-10);
  con2->Draw("ALf");

  cout << "e :" << E << " +- " << eE << endl;
  cout << "h :" << H << " +- " << eH << endl;
  cout << "k :" << K << " +- " << eK << endl;
}
