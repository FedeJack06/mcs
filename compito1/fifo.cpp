#include "fifo.h"

void fifo::buffer_push(double in){
  int n = this->size();
  if (n_operation < n)
    (*this)[n_operation] = in;
  else{
    for(int i=0; i<n-1; i++){
      (*this)[i]=(*this)[i+1];
    }
    (*this)[n-1] = in;
  }
  n_operation++;	
}
