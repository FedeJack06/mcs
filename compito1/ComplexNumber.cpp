#include "ComplexNumber.h"

std::ostream& operator<<(std::ostream& out, ComplexNumber a){
  out << std::noshowpos << a.Re() << " " << std::showpos  << a.Im() << "i";
  return out;
}

std::istream& operator>>(std::istream& in, ComplexNumber& a){
  double re,im;
  in >> re >> im;
  a.SetX(re);
  a.SetY(im);
  return in;
}

ComplexNumber ComplexNumber::Conj() const{
  return ComplexNumber(Re(), -Im());
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& b){
  double re = Re()*b.Re() - Im()*b.Im();
  double im = Re()*b.Im() + Im()*b.Re();
  return ComplexNumber(re, im);
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber& b){
  ComplexNumber denom(b.Conj()*b);
  return ( b.Conj()*(*this) )/ denom.Re();
}
//NB b.Conj() è temporaneo in memoria, quindi non posso passarlo per referenza
//referenza occorre che l'argomento sia in memoria, ossia che sia modificabile
//anche se il metodo non la modifica
//const risolvo tutto
