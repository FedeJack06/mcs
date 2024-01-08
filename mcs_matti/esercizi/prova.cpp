#include "fifo.h"
#include <iostream>

using namespace std;

int main(){
  fifo f(5);//vettore di dimensione 5
  f.add(1);
  f.add(2);
  f.add(3);
  cout<<f.size()<<endl;
  for (int i=0;i<f.size()-1;i++){
    cout<<f[i]<<" ";
  }
  cout<<endl;
  
  f.add(4);
  f.add(5);
  f.add(6);
  f.add(7);
  cout<<f.size()<<endl;
  for (int i=0;i<f.size()-1;i++){
    cout<<f[i]<<" ";
  }
  cout<<endl;
 return 0;
}
