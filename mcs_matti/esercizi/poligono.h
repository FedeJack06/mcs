#ifndef POLIGONO_H
#define POLIGONO_H
#include "TVector2.h"
#include <vector>
#include <iostream>

class poligono: public std::vector<TVector2>{
 public:
  poligono(vector<TVector2> p):vector<TVector2>(),vertice(p){}
  double perimetro();
  double area(); //solo per triangolo

 private:
  vector<TVector2> vertice;
};
#endif

double poligono::perimetro(){
  double p=0;
  for(int i=0;i<vertice.size()-1;i++){
    TVector2 segmento=vertice[i+1]-vertice[i];
    p=p+segmento.Mod();
  }
  //manca il segmento che congiunge l'ultimo punto al primo
  TVector2 segmento_=vertice[0]-vertice[vertice.size()-1];
  p=p+segmento_.Mod();
  return p;
}

double poligono::area(){
  double a=0;
  if(vertice.size()==3){
    TVector2 ab=vertice[1]-vertice[0];
    TVector2 ac=vertice[2]-vertice[0];
    a=(ab^ac)/2;
  }else{std::cout<<"il poligono non è un triangolo"<<std::endl;}
  return a;
}
