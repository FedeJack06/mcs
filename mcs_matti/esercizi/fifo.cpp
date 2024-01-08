#include "Vector.h"
#include "fifo.h"


int counter=0;

fifo fifo::add(double c){
  int max_size=d;
  if(counter<max_size){
    this->push_back(c);
    counter=counter+1;
  }else{
    for (int i=d-1;i>=0;i--){
    v[i-1]=v[i];
    }
    v[d-1]=c;
  }
  return *this;
}

  
  
