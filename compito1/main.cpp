#include <iostream>
#include "ComplexNumber.h"

int main(){
  ComplexNumber a(10, 12), b;
  std::cout << "a = " << a << std::endl;
  std::cout << "inserire parte reale e immaginaria di b: " << std::flush;
  std::cin >> b;
  std::cout << "b = " << b << std::endl;
  std::cout << "b* = " << b.Conj() << std::endl;
  std::cout << "a+b= " << a+b << std::endl;
  std::cout << "a-b= " << a-b << std::endl;
  std::cout << "a*b= " << a*b << std::endl;
  std::cout << "2*b= " << 2*b << std::endl;
  std::cout << "b*2= " << b*2 << std::endl;
  std::cout << "a/b= " << a/b << std::endl;
  return 0;
}
