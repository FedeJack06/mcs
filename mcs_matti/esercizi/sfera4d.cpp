#include <TMath.h>
#include <iostream>
#include <TRandom3.h>

using namespace std;

int main(){
  double R=1;

  double ntot=1e08;
  double nacc=0;

  TRandom3 rnd;
  rnd.SetSeed(462947);

  //genero il cubo e calcolo quali siano i punti accettati
  for(int j=0;j<ntot;j++){
    double x=2*R*rnd.Rndm()-R;
    double y=2*R*rnd.Rndm()-R;
    double z=2*R*rnd.Rndm()-R;
    double t=2*R*rnd.Rndm()-R;

    //raggio generato ad ogni ciclo
    double r=sqrt(x*x + y*y + z*z + t*t); 

    //controllo che il raggio generato sia minore del raggio della sfera
    if(r<=R){
      nacc=nacc+1;
    }
  }

  //probabilità che sia un valore della sfera
  double p=nacc/ntot;
  double vol=p*pow(2*R,4); //probabilità per volume dominio di generazione

  //il volume della sfera sarà alpha*r**4, mi faccio printare alpha

  double alpha=vol/(pow(R,4));

  //verifico che sia uguale alla formula di merda
  double pippo= pow(TMath::Pi(),4/2)/(TMath::Gamma((4/2)+1));
  
  cout<<"p "<<p<<" vol "<<vol<<" alpha "<<alpha<<" alpha_vero "<<pippo<<endl;
}
