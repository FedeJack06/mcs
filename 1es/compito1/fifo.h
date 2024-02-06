#ifndef _FIFO
#define _FIFO
#include <iostream>
#include <vector>

class fifo: public std::vector<double>{
public:
  using std::vector<double>::vector;
  fifo(int n): std::vector<double>(n) {};
  
  void buffer_push(double);

private:
  int n_operation=0;
};
#endif
