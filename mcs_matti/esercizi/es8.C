{
  /*
   *
   *programma per l'utilizzo di mnemat che estrae la covarianza da un fit
   *
   */
  ifstream ifile("daties8.dat");
  TH1D *h=new TH1D("h","title",45,-1,1);
  
  /*funzione con relativo fattore di normalizzazione opportuno
   *ottenuto integrando nel dominio -1 1*/
  TF1 *f=new TF1("f","[2]*(1/(2+(2./3.)*[0]))*(1+[1]*x+[0]*x*x)",-1,1);

  double theta;
  //definizione di una matrice vuota 2x2, da utilizzare per mnemat
  double cov[3][3];

  while(ifile>>theta){
    h->Fill(theta);
  }   
  h->Draw();

  //f->FixParameter(2,1);
  f->FixParameter(2,h->GetEntries()*h->GetBinWidth(2));
  h->Fit("f","L");
  gMinuit->mnemat(&cov[0][0], 3);

  cout<<"correlazione "<<cov[0][1]/(f->GetParError(0)*f->GetParError(1))<<endl;

  double alpha =f->GetParameter(1);
  double ealpha=f->GetParError(1);
  double beta=f->GetParameter(0);
  double ebeta=f->GetParError(0);
  double gamma=3*alpha-2*beta;
  double egamma=sqrt(pow(3*ealpha,2)+pow(2*ebeta,2)+2*cov[0][1]*(-6));

  cout<<"miglior stima di gamma "<<gamma <<" +/- "<<egamma<<endl; 
 
}
