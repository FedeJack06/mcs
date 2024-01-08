//---------------------------------------------------------------------------------------------------//
//Tutte le classi, nel file .h (o se IMPLEMENTATE SOLAMENTE nel file .cpp), devono essere racchiuse in:
//---------------------------------------------------------------------------------------------------//
#ifndef _NOMECLASSE
#define _NOMECLASSE

//Tutto quello che riguarda la classe e le funzioni da definire dopo la classe

#endif

//*****************************************************//
/*ESEMPIO CON COSTRUZIONI INTERESSANTI: NumeriComplessi*/
//*****************************************************//

//--------------------------------------------------//
//Si includono le classi necessarie al funzionamento//
//--------------------------------------------------//
#include "NumeriComplessi.h"
#include <TVector2.h>
#include <cmath>
#include <iostream>

using namespace std;

NumeriComplessi NumeriComplessi::Coniugato(){

  NumeriComplessi ris;
  ris.Re(Re());
  ris.Im(-Im());

  return ris;

}

NumeriComplessi NumeriComplessi::operator-(){
  
  NumeriComplessi opposto;
  opposto.Re(-Re());
  opposto.Im(-Im());

  return opposto;

}

NumeriComplessi NumeriComplessi::operator*(double u){

  NumeriComplessi ris;
  ris.Re(u*Re());
  ris.Im(u*Im());

  return ris;

}

NumeriComplessi operator*(double u,  const NumeriComplessi& c){
  return c*u;
}

NumeriComplessi NumeriComplessi::operator*(NumeriComplessi w){
  
  NumeriComplessi ris;
  ris.Re(Re()*w.Re()-Im()*w.Im());
  ris.Im(Re()*w.Im()+Im()*w.Re());

  return ris;

}


std::ostream& operator<<(std::ostream& os, const NumeriComplessi& c){
  
  if(c.Im()>0){
    os<<c.Re()<<"+";
    os<<c.Im()<<"i";
  }

  else if(c.Im()<0){
    os<<c.Re()<<"-";
    os<<-c.Im()<<"i";
  }

  else
    os<<c.Re();
  
  return os;
}

//********************************************//
/*ESEMPIO CON COSTRUZIONI INTERESSANTI: Vector*/
//********************************************//

//--------------------------------------------------//
//Si includono le classi necessarie al funzionamento//
//--------------------------------------------------//
#include "Vettore.h"
#include <cmath>
#include <iostream>

double Vettore::X() const{
  return m_v[0];
}

double Vettore::Y() const{
  return m_v[1];
}

double Vettore::Z() const{
  return m_v[2];
}

void Vettore::X(double x){
  m_v[0] = x;
}

void Vettore::Y(double y){
  m_v[1] = y;
}

void Vettore::Z(double z){
  m_v[2] = z;
}

Vettore Vettore::operator-(){
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = -m_v[i];
  }
  return res;
}


Vettore Vettore::operator-(const Vettore& b) const{
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i] - b.m_v[i];
  }
  return res;
}

Vettore Vettore::operator+(const Vettore& b) const{
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i] + b.m_v[i];
  }
  return res;
}

double Vettore::operator*(const Vettore& b) const{
  double prod=0;
  for (int i=0;i<3;i++){
    prod += m_v[i]*b.m_v[i];
  }
  return prod;
}

Vettore Vettore::Cross(const Vettore& b) const{
  Vettore res;
  res.X(m_v[1]*b.m_v[2]-m_v[2]*b.m_v[1]);
  res.Y(m_v[2]*b.m_v[0]-m_v[0]*b.m_v[2]);
  res.Z(m_v[0]*b.m_v[1]-m_v[1]*b.m_v[0]);
  return res;
}

Vettore Vettore::operator*(double f) const{
  Vettore res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i]*f;
  }
  return res;
}

double Vettore::Mod() const {
  return sqrt((*this)*(*this));
}

Vettore Vettore::Vers() const {
  return (*this)*(1/Mod());
}

Vettore operator*(double f,  const Vettore& b){
  return b*f;
}

std::ostream& operator<<(std::ostream& os,  const Vettore& b){
  os << "(";
  os << b.X() << ",";
  os << b.Y() << ",";
  os << b.Z() << ")";
  return os;
}

std::istream& operator>>(std:: istream& is, Vettore& b){
  double x,y,z;
  is >> x >> y >> z;
  b  = Vettore(x,y,z);
  return is;
}

//******************************************************//
/*ESEMPIO DERIVAZIONE E COMPOSIZIONE: Particle, MatPoint*/
//******************************************************//

//--------------------------------------------------//
//Si includono le classi necessarie al funzionamento//
//--------------------------------------------------//
#include "MatPoint.h"
#include "Vector.h"
#include <cmath>

Vector MatPoint::R(){
  return m_r;
}

Vector MatPoint::V(){
  return m_v;
}

void MatPoint::R(Vector r){
  m_r = r;
}

void MatPoint::V(Vector v){
  m_v = v;
}

Vector MatPoint::GravField(Vector r){
  // F = -G m m_prova/(r-r0)^2 vers(r-r0)
  // a = F/m_prova = -G m /(r-r0)^2 vers(r-r0)
  Vector r0   = m_r;
  Vector dist = r-r0;

  Vector val  = -consts::G*Mass()/pow(dist.Mod(),2)*dist.Vers();

  return val;
}

//***********************************************************//
/*ESEMPIO CON COSTRUZIONI INTERESSANTI: myTF1                */
/*DERIVAZIONE CON COSTRUTTORE COMPLESSO A PARTIRE CLASSE BASE*/
//***********************************************************//

//--------------------------------------------------//
//Si includono le classi necessarie al funzionamento//
//--------------------------------------------------//
#include<TF1.h>
#include<vector>
#include"myTF1.h"

double myTF1::ZeriNR(double a, double b, double iter) const{
  double x_i   = a;
  for(int i = 0; i<iter; i++){
    if(x_i<=b){
      double x_i_1 = x_i - Eval(x_i)/Derivative(x_i);
      x_i = x_i_1;
	}
  }

  return x_i;
}

//*************************************************************//
/*ESEMPIO CON COSTRUZIONI INTERESSANTI: poly                   */
/*IMPLEMENTAZIONE IN UN SOLO COLPO DEL FILE .h, .cpp e MAIN.cpp*/
//*************************************************************//

//--------------------------------------------------//
//Si includono le classi necessarie al funzionamento//
//--------------------------------------------------//

#ifndef _POLY
#define _POLY

#include<vector>
#include<cmath>
#include<iostream>

using namespace std;

class poly: public vector<double>{

public:

  //Costruzione con lista di assegnazione
  poly(int n = 3):vector<double>(n){}
  
  poly(double p0, double p1, double p2 = 0, double p3 = 0):vector<double>{p0,p1,p2,p3}{}

  //Operatori
  poly operator+(const poly& p);

  //Metodi
  double eval(double x);
  

};

poly poly::operator+(const poly& p){

  poly sum(p.size());

  for(int i = 0; i<p.size(); i++)
    sum.at(i) = at(i)+p.at(i);
  //sum[i] = (*this)[i] + b[i];

  return sum;
}

double poly::eval(double x){
  
  double sum = 0;

  for(int i = 0; i<size(); i++)
    sum += pow(x,i)*at(i);
  //sum += pow(x,i)*(*this)[i];

  return sum;

}
#endif

int main(){
  poly a(1,2,3); //passo valori
  poly b(2,2,3); //passo valori
  poly sum(3);   //definisco solo la dimensione

  sum = a+b;
  cout << sum.eval(2) << endl;
  return 0;
}

//---------------------------------------------------------------//
//Compilazione: solo con nome file classe.cpp che include il main//
//---------------------------------------------------------------//
g++ --std=c++11 -o poly poly.cpp $(root-config --glibs --cflags)
			 
