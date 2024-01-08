{
  rnd = TRandom3();
  rnd.SetSeed(114506534);

  double R = 4;
  double Ntot = 4000000; //n tot nel cubo xyz di lato R
  double Nsfera = 0; //n punti casuali appartenenti alla sfera
  for(int i=0; i<Ntot; i++){
    double x = R*rnd.Rndm(); //Rnd genera casuale tra 0 e 1
    double y = R*rnd.Rndm();
    double z = R*rnd.Rndm();
    double r_sfera = sqrt(x*x + y*y + z*z);
    if (r_sfera < R)
      Nsfera++;
  }

  //Ntot : Nsfera = Vtot : Vsfera
  //Vsfera = Nsfera*Vcubo/Ntot

  double rapporto = Nsfera/Ntot;
  double e_rapporto = sqrt(rapporto*(1-rapporto)/Ntot);

  double Vcubo = pow(2*R, 3); //cubo che contiene la sfera ha lato 2R
  double Vsfera = rapporto*Vcubo;
  double e_Vsfera = e_rapporto*Vcubo;
  cout << "V sfera MC: " << Vsfera << " +/- " << e_Vsfera << endl;
  cout << "V sfera id: " << 4./3.*TMath::Pi()*pow(R, 3) << endl;
}
