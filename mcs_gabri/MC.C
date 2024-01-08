//**********//
//HANDS ON 1//
//**********//

//*******************************************************************//
//PROGRAMMA 1: testo a disposizione su aulaweb, MACRO UNNAMED DI ROOT//
//RILEVATORE CON PROPAGAZIONE DA SORGENTE ISOTROPA                   //
//*******************************************************************//
{

  double L=0.01;
  double d=0.20;

  TRandom3 rnd;
  rnd.SetSeed(123456789);
  int ntot = 100000;
  int n1 = 0;
  int n2 = 0;

  //Distribuzioni uniformi di phi e costheta
  for(int i=0;i<ntot; i++){
    double phi = 2*TMath::Pi()*rnd.Rndm(); //nei giusti intervalli
    double costheta = 2*rnd.Rndm()-1;
    double theta = acos(costheta);
    //a questo punto determinata direzione del fotone
    double alpha = d/costheta;
    if(theta > TMath::Pi()/2) continue; //butto via angoli indietro
    double x = alpha*cos(phi)*sin(theta);
    double y = alpha*sin(phi)*sin(theta);
    if(abs(x)<L/2 && abs(y)<L/2){
      n1++; //conto le volte in cui fotone va a sbattere
  }
    if(x>-L && x<0 && y>0 && y<L){
      n2++;
    }

}

  double p = (double)n1/ntot;
  double ep = sqrt(p*(1-p)/ntot); //errore della binomiale per vedere se compatibile con caso approssimato
  cout << "p " << p <<"+/-"<<ep<< endl;
  cout << "Approssimazione d>>L: " << L*L/(4*TMath::Pi()*d*d)<<endl;//se aumento troppo L, non più compatibili
  double p2 = (double)n2/ntot;
  double ep2 = sqrt(p2*(1-p2)/ntot); //errore della binomiale per vedere se compatibile con caso approssimato
  cout << "p2 " << p2 <<"+/-"<<ep2<< endl;
}

