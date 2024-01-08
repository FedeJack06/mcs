{
  rnd = TRandom3();
  rnd.SetSeed(114506534);

  double R = 1;
  double Ntot = 4000000; //n tot nel cubo xyz di lato R
  double Nsfera = 0; //n punti casuali appartenenti alla sfera
  for(int i=0; i<Ntot; i++){
    double x = R*rnd.Rndm(); //Rnd genera casuale tra 0 e 1
    double y = R*rnd.Rndm();
    double z = R*rnd.Rndm();
    double t = R*rnd.Rndm();
    double r_sfera = sqrt(x*x + y*y + z*z + t*t);
    if (r_sfera < R) //considero 1/8 di sfera nel cubo di lato R
      Nsfera++;
  }

  //Ntot : Nsfera = Vtot : Vsfera
  //Vsfera = Nsfera*Vcubo/Ntot

  double rapporto = Nsfera/Ntot;
  double e_rapporto = sqrt(rapporto*(1-rapporto)/Ntot);

  double Vcubo = pow(2*R, 4); //nel cubo ci sta 1/8 di sfera
  double Vsfera = rapporto*Vcubo;
  double e_Vsfera = e_rapporto*Vcubo;
  cout << "V sfera MC: " << Vsfera << " +/- " << e_Vsfera << endl;
  cout << "V= alpha*R^4, alpha: " << Vsfera/pow(R, 4) << endl;
  cout << "alpha ideale: " << pow(TMath::Pi(), 2)/TMath::Gamma(4./2. + 1) << endl;
}
