#include "Vector3.h"
//#include <cmath>



Vector3 Vector3::operator+(Vector3 b){
  Vector3 sum;
  for (int i=0;i<3;i++)
    sum.m_v[i] = m_v[i]+b.m_v[i];
    //ritorno   e' in a+    in b
  return sum;
}

Vector3 Vector3::operator*(double f){
  Vector3 v;
  for (int i=0;i<3;i++)
    v.m_v[i] = f*m_v[i];
  return v;
}

Vector3 Vector3::operator-(){
  Vector3 v;
  for (int i=0;i<3;i++)
    v.m_v[i] = -m_v[i];
  return v;
}

double Vector3::X(){
  return m_v[0];
}

double Vector3::Y(){
  return m_v[1];
}

double Vector3::Z(){
  return m_v[2];
}

void Vector3::X(double x){
  m_v[0] = x;
}

void Vector3::Y(double y){
  m_v[1] = y;
}

void Vector3::Z(double z){
  m_v[2] = z;
}

Vector3 operator*(double f, Vector3 a){
  return a*f;
}

std::ostream& operator<<(std::ostream& output, Vector3 a){
  output << "(" << a.X() << "," << a.Y() << "," << a.Z() << ")";
  return output;
}

std::istream& operator>>(std::istream& input, Vector3& a){
  double x,y,z;
  input >> x >> y >> z;
  a.X(x); a.Y(y); a.Z(z);
  return input;
}

double Vector3::module(){   
  double sum = 0;
  for(int i=0; i<3; i++){
    sum += pow((*this).m_v[i], 2);
  }
  double module = pow(sum,0.5);
  return module;
}

Vector3 Vector3::versor(){
  Vector3 versore = (*this)*(1/this->module());
  return versore;
}