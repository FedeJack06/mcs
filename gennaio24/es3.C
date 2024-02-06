/*
Il numero di eventi piovosi in un periodo segue la distribuzione di Poisson con parametro 1.9
La quantità di acqua per evento segue la Raylegh (f1)
Graficare in histogramma 2d il numero di temporali e la pioggia totale
Trovare la probabilità di ottenere stazione siccitosa con cm pioggia caduti < 4 cm
*/
{
  rnd = TRandom3();
  rnd.SetSeed(123456789);

  double Ntot = 10000;
  double a=9e-4, b=0.03;
  TF1 *f1 = new TF1("f1","2./0.0009*x*TMath::Exp(-pow(x/0.03, 2))");
  int Nsicc = 0; //n temporali con mmPioggia < 40

  TH2D *histo = new TH2D("histo", "", 100, 0., 0., 100, 0., 0.);
  for(int i=0; i<Ntot; i++){
    int temporali = rnd.Poisson(1.9); //n di temporali nel periodo (genero un valore casuale secondo poisson(1.9))
    double mmTot = 0;
    for (int b=1; b<=temporali; b++){ //per ogni temporale calcolo i mm caduti (segue rayleigh)
      double random = rnd.Rndm();
      double mm = sqrt(-b*b*log(1-a/(b*b)*random)); //mm per singolo temporale (casuale secondo rayleigh, metodo inversione)
      mmTot = temporali*mm; //mm tot della stagione
    }
    histo->Fill(temporali, mmTot);
    if (mmTot < 0.04)
      Nsicc++;
  }
  histo->GetXaxis()->SetTitle("n eventi piovosi");
  histo->GetYaxis()->SetTitle("pioggia totale [mm]");
  histo->Draw();

  cout << "Probabilità avere periodo siccitoso: " << (double)Nsicc/Ntot << endl;

/*VERIFICO DI AVER OTTENUTO DISTR RAYLIGH DAL METODO DI INVERSIONE
  TH1D *ray = new TH1D("ray", "verifico che sia Rayleigh", 1000, 0., 0.);
  for(int i=0; i<1000000; i++){
    double random = rnd.Rndm();
    ray->Fill(sqrt(-b*b*log(1-a/(b*b)*random)));
  }
  TCanvas *c2 = new TCanvas("c1", "c1", 1200, 800);
  c2->cd();
  ray->Draw();*/
  //verifico che valore medio è circa 0.03
}
