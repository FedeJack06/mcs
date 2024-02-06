{
    ifstream ifile("DatiGamma.dat");
    double tmp;
    int Nbin = 50;
    TH1D *histo = new TH1D("histo", "", Nbin, 0., 26.5);
    while(ifile >> tmp){
        histo->Fill(tmp);
}
    histo->Draw();
    TF1 *f1 = new TF1("f1", "[1]*((pow(x,2)*exp(-x/[0]))/(2*pow([0],3)))");
    f1->SetParameter(1,histo->GetBinWidth(1)*histo->GetEntries());
    f1->SetParameter(0,0.01);
    histo->Fit("f1", "L");
    cout << f1->GetProb() << endl;
}