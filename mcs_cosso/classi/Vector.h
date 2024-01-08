#include <iostream>

class Vector;

std::ostream& operator<<(std::ostream&,Vector&);
Vector operator*(double , Vector&);

class Vector{
 public:

 // costruttore
	Vector(double x=0, double y=0, double z=0):m_v{x,y,z}{}; //costruttore per lista
	                                                         //assegnazione nel corpo se valori assegnati dentro a {}
	
 //getters and setters
  double X();
  double Y();
  double Z();
  void X(double);
  void Y(double);
  void Z(double);

  //prodotto scalare
  double operator*(Vector&) ;
  
  //prodotto vettore
  Vector prodVettore(Vector&);

  //prodotto per scalare
  Vector operator*(double);
 
  //versore
  Vector versore();
  
  //modulo
  double module();

  //somma
  Vector operator+(Vector&) ;
  
  
private:

  double m_v[3];

};

/*
________________________________________________________________________________________________

#include "Vector.h"
#include <cmath>
#include <iostream>

using namespace std;

*/

//setters and getters 
double Vector::X(){
  return m_v[0];
}

double Vector::Y(){
  return m_v[1];
}

double Vector::Z(){
  return m_v[2];
}

void Vector::X(double x){
  m_v[0] = x;
}

void Vector::Y(double y){
  m_v[1] = y;
}

void Vector::Z(double z){
  m_v[2] = z;

}


//prodotto scalare
double Vector:: operator*(Vector& v){

  double a = (this->X()*v.X() + this->Y()*v.Y() + this->Z()*v.Z());
  return a;

}

//prodotto vettore
Vector Vector::prodVettore(Vector& w){
  
  Vector k;
  k.X(this->Y()*w.Z()-this->Z()*w.Y());
  k.Y(this->Z()*w.X()-this->X()*w.Z());
  k.Z(this->X()*w.Y()-this->Y()*w.X());

  return k;
  
}

//prodotto per scalare

Vector Vector::operator*(double a){

  Vector v;
  v.X(a*m_v[0]);
  v.Y(a*m_v[1]);
  v.Z(a*m_v[2]);

  return v;
}


//modulo
double Vector::module(){

  double m;
  m = sqrt((*this)*(*this));
  //m = this->X()*this->X() + this->Y()*this->Y() + this->Z()*this->Z();
  return m;
}

Vector Vector:: operator+(Vector& v){

  Vector sum;
  sum.X(this->X()+v.X());
  sum.Y(this->Y()+v.Y());
  sum.Z(this->Z()+v.Z());
  return sum;
}


//versore
Vector Vector::versore(){

  Vector k;
  k.X((this->X())/(this->module()));
  k.Y((this->Y())/(this->module()));
  k.Z((this->Z())/(this->module()));
  return k;
}

//operatore print
ostream &operator<<(ostream& o, Vector& v){
  o << "("<< v.X() << "," << v.Y() << "," << v.Z() << ")";
  return (o);
}

Vector operator*(double a, Vector& v){
  return v*a;
}
