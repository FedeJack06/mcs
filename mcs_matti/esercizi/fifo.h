#ifndef FIFO_H
#define FIFO_H
#include <iostream>
#include <cmath>
#include <vector>

class fifo: public std::vector<double> {
 public:
  fifo(int a):vector<double>(),d(a){} //costruttore di un vettore di dimensione fissata

  fifo add(double); //metodo per inserire dei valori nel vettore creato
  //i valori vengono inseriti in fondo
  
 private:
  vector <double> v;
  int d;
  
};

#endif
