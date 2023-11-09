#ifndef _COMPLEXNUMBER
#define _COMPLEXNUMBER

#include <TVector2.h>
#include <iostream>

class ComplexNumber : public TVector2{
public:
  using TVector2::TVector2;
  ComplexNumber(TVector2 z):TVector2(z){};
  
  double Re() const { return fX; }; //getter real part
  double Im() const { return fY; }; //getter immaginary part
  ComplexNumber Conj() const;       //complex conjugate
  
  ComplexNumber operator*(const ComplexNumber&);
  ComplexNumber operator/(const ComplexNumber&);
};

std::ostream& operator<<(std::ostream& out, ComplexNumber a);
std::istream& operator>>(std::istream& in, ComplexNumber& a);

#endif
