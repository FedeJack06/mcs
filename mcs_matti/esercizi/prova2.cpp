#include "poligono.h"
#include <iostream>

using namespace std;

int main(){
  TVector2 v1(1,15);
  TVector2 v2(4,6);
  TVector2 v3(7,10);
  //TVector2 v4(11,0);
  vector<TVector2> v={v1,v2,v3};

  poligono p(v);

  cout<<p.perimetro()<<endl;
  cout<<p.area()<<endl;
}
