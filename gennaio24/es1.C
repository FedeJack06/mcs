/*
Calcolare Chi^2 si Pearson, Neyman, Likehood senza usare metodi di root
Calcolare pi value nel caso di exp (boh non ricordo)
Calcolare pi value nel caso di fit likehood (boh non ricordo)
*/
double fun(double x){//par = 2
  return 0.5*TMath::Exp(-x/2.);
}

void es1(){
  ifstream ifile("dati_exp.dat");
  double tmp;
  int Nbin = 30;
  TH1D *histo = new TH1D("histo", "", Nbin, 0., 12.);
  while(ifile >> tmp){
    histo->Fill(tmp);
  }
  histo->Draw();

  //calcolo chi^2 person bin per bin
  double pearson = 0.0;
  for (int i=1; i<=Nbin; i++){
    pearson += pow(histo->GetBinContent(i)-fun(histo->GetBinCenter(i)),2)/fun(histo->GetBinCenter(i));
  }
  cout<<"chi pearson "<< pearson << endl;

  //calcolo chi^2 neyman bin per bin
  double neyman = 0.0;
  for (int i=1; i<=Nbin; i++){
    if (histo->GetBinContent(i) != 0)
      neyman += pow(histo->GetBinContent(i)-fun(histo->GetBinCenter(i)),2)/pow(histo->GetBinError(i),2);
  }
  cout<<"chi neyman " << neyman << endl;

  //calcolo chi^2 likehood bin per bin
  double likehood = 0.0;
  double L = 1, Lsat=1;
  for (int i=1; i<=Nbin; i++){
    double n = histo->GetBinContent(i);
    double y = fun(histo->GetBinCenter(i));
    if (n != 0){
      //L = L*exp(-y)*pow(y,n)/TMath::Factorial(n);
      //Lsat = Lsat*exp(-n)*pow(n,n)/TMath::Factorial(n);
      //cout << L << " " << Lsat << endl;
      likehood += 2*(y-n+n*log(n/y));
    }
  }
  //likehood = -2*log(L/Lsat);
  cout << "chi likehood " << likehood << endl;

//verifico andamento pdf exp graficamente
  TF1 *f1 = new TF1("f1", "[0]*0.5*TMath::Exp(-x/2.)", 0., 12.);
  f1->SetParameter(0, histo->GetEntries()*histo->GetBinWidth(1));
  cout<<"norm " << f1->GetParameter(0) << endl; //con normalizz = 400, chi quadri molto minori
  f1->Draw("SAME");
 }
