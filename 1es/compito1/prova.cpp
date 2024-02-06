#include <iostream>
#include "fifo.h"

int main(){
  int dim;
  std::cout << "dim buffer: " << std::flush;
  std::cin >> dim;
  fifo buffer(dim);
  while(true){
    std::cout << "push in buffer :" << std::flush;
    double tmp;
    std::cin >> tmp;
    buffer.buffer_push(tmp);
    
    for(int i=0; i < buffer.size(); i++)
      std::cout << buffer[i] << " " << std::flush;
    std::cout << std::endl;
  }
  return 0;
}
