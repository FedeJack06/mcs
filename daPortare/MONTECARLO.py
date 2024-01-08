##############################INTEGRALE HANDS ON
import ROOT
import math

rnd = ROOT.TRandom3()
rnd.SetSeed(158375846)

R = 1
Rcl = R/2
Ntot=4000000 #errore come rad(conteggio) aumento fattore 4, errore si dimezza
Nacc = 0
Nacc_sph = 0
for i in range(Ntot):
    x = (2*rnd.Rndm()-1)*R #cerco punti casuali fuori dalla sfera
    y = (2*rnd.Rndm()-1)*R #punti casuali generati fra 1 e 2
    z = (2*rnd.Rndm()-1)*R
    r = math.sqrt(x*x+y*y+z*z)
    rcl = math.sqrt(x*x+y*y)
    if r<R and rcl>R/2:
        Nacc += 1
    if r<R:
        Nacc_sph += 1

p = Nacc/Ntot
ep = math.sqrt(p*(1-p)/Ntot)

ps = Nacc_sph/Ntot
eps = math.sqrt(ps*(1-ps)/Ntot)

vol = (2*R)**3

print("vol solido: %6.3f +- %6.3f"%(p*vol, ep*vol))
print("vol sfera ideale: %6.3f",4/3.*math.pi*R**3)
print("vol sfera monte carlo: %6.3f +- %6.3f"%(ps*vol, eps*vol))

######################################################################
############### MONTECARLO HANDS ON
import ROOT
import math

rnd = ROOT.TRandom3()
rnd.SetSeed(165786865)

f = 0.3
tau1 = 0.1
tau2 = 1
tauacc = 0.01

Ntot =  10000
#100 bin, exp veloce e exp lento => metto 0.5 per presentare bene entrambi
h = ROOT.TH1D("hist","tempi di decadimento",1000,0,5)
h2 = ROOT.TH1D("hist2","tempi misurati",1000,0,5)
for i in range(0, Ntot, 1): #i++
    #p(t) divisa in due naturalmente
    #processo binomiale, controllo se atomo della sostanza 1 o 2
    if rnd.Rndm()<f:
        #sono in sostanza 1
        t = -tau1*math.log(rnd.Rndm())
    else:
        #sono in sostanza 2
        t = -tau2*math.log(rnd.Rndm())
    h.Fill(t)
    #tempi misurati è un altro problema binomiale che tipende dal tempo
    if rnd.Rndm() < 1-math.exp(-t/tauacc):
        #t = rnd.Gaus(t, ris)
        h2.Fill(t)
h.Draw()
ROOT.gApplication.Run(True)

h2.Draw("SAME") #1000 bin si nota differenza fra due isto
h2.SetLineColor(2)
ROOT.gApplication.Run(True)

#######################################################################
################## RADIOATTVITÀ HANDS ON C++
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

###########################################################################
################### SFERA 3D
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

#######################################################################
################# SFERA 4D
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


