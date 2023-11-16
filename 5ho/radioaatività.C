{
  /* rilevatore di lato l a distanza d dalla sorgente emettitrice (uniforme)
     calcolare la frazione di potenza rilevata
     se l piccolo rispetto d la frazione è ben approssimata da sup_quadrato/sup_sfera
     altrimento integro l'angolo solido
     Con Monte Carlo conto particelle emesse e rilevate*/

  TRandom3 rnd;
  rnd.SetSeed(175976946);

  int Ntot= 100000000; //se non preciso aumento eventi
  double d = 0.2;
  double L = 0.05;
  double Nacc = 0, Nacc2=0;

  for (int i=0; i<Ntot; i++){
    double phi = 2*TMath::Pi()*rnd.Rndm();
    double costheta = 2*rnd.Rndm()-1;
    double theta = acos(costheta);
    if (theta < TMath::Pi()/2){
      double s = d/costheta;
      double x = cos(phi)*sin(theta)*s;
      double y = sin(phi)*sin(theta)*s;
      if (abs(x)<L/2 && abs(y)<L/2)
	Nacc++;
      if (x>0 && x<L && y>0 && y<L)
	Nacc2++;
    }
  }
  double p = (double)Nacc/Ntot;
  double ep = sqrt(p*(1-p)/Ntot);
  cout << "Accettanza misura 1 " << p << " +/- " << ep << endl;
  
  double p2 = (double)Nacc2/Ntot;
  double ep2 = sqrt(p2*(1-p2)/Ntot);
  cout << "Accettanza misura 2 " << p2 << " +/- " << ep2 << endl;
  
  double p_app = L*L/(4*TMath::Pi()*d*d);
  cout << "Accettanza approx (L << d) " << p_app << endl;
}
