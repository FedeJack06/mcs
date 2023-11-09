//#include "Electron.h"
#include "MatPoint.h"
#include <iostream>
#include "Electron.h"
#include <fstream>

using namespace std;

int main(){
  double mass=121;
  double charge=1e-6;
  MatPoint p1(Particle(mass, charge), Vector3(1,1,0), Vector3(2,0,0));

  cout << "carica " << p1.Charge() << endl;
  cout << "massa " << p1.Mass() << endl;
  cout << "posizione massa " << p1.R() << endl;
  cout << "massa " << p1.V() << endl;

  cout << "campo gravitazionale " << p1.GravField(Vector3(-1,-1,0)) << endl;

  cout << "e " << Electron().Charge() << endl;
  cout << "m_e " << Electron().Mass() << endl; 

  /*
  //Costruzione da particella "nota"
  MatPoint p(Electron(),Vector3(1,0,0));
  cout << p.Mass() << " " << p.Charge() << endl;
  cout << p.R() << endl;
  cout << p.V() << endl;

  //Costruzione punto materiale generico
  MatPoint pm(1,0,Vector3(1,0,0),Vector3(1,1,1));
  cout << pm.Mass() << " " << pm.Charge() << endl;
  cout << pm.R() << endl;
  cout << pm.V() << endl;


  // Calcolo Campo Gravitazionale
  Vector3 v = pm.GravField(Vector3(1.5,0,0));
  if (v.X()!=-4){
    cout << "Errore campo vettoriale:" << endl;
    cout << " valore aspettato -4, ottenuto " << v.X() << endl;
  }
  */
  
}
