#ifndef _VECTOR3
#define _VECTOR3

#include <iostream>
#include <cmath>

class Vector3{
 public:
  Vector3(double x=0, double y=0, double z=0):m_v{x,y,z}{};
  Vector3 operator+(Vector3);
  Vector3 operator-();
  Vector3 operator*(double);
  double X();
  double Y();
  double Z();
  void X(double);
  void Y(double);
  void Z(double);

  double module();
  Vector3 versor();

 private:
  double m_v[3];
};

Vector3 operator*(double f, Vector3 a);
std::ostream& operator<<(std::ostream& output, Vector3 a);
std::istream& operator>>(std::istream& input, Vector3& a);

#endif
