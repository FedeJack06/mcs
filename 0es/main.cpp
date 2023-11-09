#include "Vector3.h"
#include <iostream>

using namespace std;

int main(){
  Vector3 b(1,1,1);
  Vector3 a(1);
  Vector3 d,e,f,g;

  d = a+b;
  e = -b;
  f = a*5;
  g = 5*a;
  cout << d.X() << " " << d.Y() << " " << d.Z() << endl;
  cout << e.X() << " " << e.Y() << " " << e.Z() << endl;
  cout << f.X() << " " << f.Y() << " " << f.Z() << endl;
  cout << g.X() << " " << g.Y() << " " << g.Z() << endl;

  cout << "Il vettore a vale " <<  a << endl;

  cin >> a;
  cout << a << endl;

  cout << "modulo(a) " << a.module() << endl;
  cout << "versore(a) " << a.versor() << endl;
  cout << "modulo versore(a) " << a.versor().module() << endl;

  return 0;

}
