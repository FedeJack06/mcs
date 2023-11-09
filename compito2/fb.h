#ifndef _FB
#define _FB
#include <TMath.h>

//Campo Magnetico della "Bottiglia"
Vector3 CampoBottiglia(Vector3 r){
  double BMin= 1.4e-5, BMax=7e-5;
  double BottleLen= 10.0;
  double rho= sqrt(r.X()*r.X()+r.Y()*r.Y());
  double phi= atan2(r.Y(),r.X());
  double Bz= BMin+(BMax-BMin)*(1 + 1/2.*(TMath::Erf(r.Z()-BottleLen/2) - TMath::Erf(r.Z()+BottleLen/2)));
  double DerivBZ= (BMax-BMin)/sqrt(M_PI)*(TMath::Exp(-pow(r.Z()-BottleLen/2,2))-TMath::Exp(-pow(r.Z()+BottleLen/2,2)));
  double Br= -DerivBZ*rho/2;
  double Bx= Br*cos(phi);
  double By= Br*sin(phi);
  return Vector3(Bx,By,Bz);
}
#endif
