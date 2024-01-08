#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <cmath>

class Vector{
    public:
      //Vector();                              //costruttore vuoto
      //Vector(double x, double y,double z);   //costruttore che richiede argomenti

      //oppure in c++11 
      Vector(double x=0, double y=0, double z=0):m_v{x,y,z}{}
      //Vector():m_v{0,0,0}{}

      //se voglio fare vettori che abbiano sia 0 che 1,2,3 argomenti fisso dei valori  
      //Vector(double x=0,double y=0,double z=0);

      //aggiungiamo metodi per accedere o modificare il vettore
      double X();
      double Y();
      double Z();       //ritorna il valore della x
      void X(double);   //cambia il valore della x sostituendolo in main va usato con v.X(double)
      void Y(double);
      void Z(double);


      //definiamo gli operatori matematici tra vettori e implementiamo il metodo in vector.cpp
      Vector operator+(Vector);   //operatore binario
      Vector operator-();         //operatore unario
      Vector operator*(double);         //prodotto per scalare
      double operator*(Vector);   //prodotto scalare
      Vector operator^(Vector);   //prodotto vettore

      double modulo();

      Vector versore(){
        double q= 1/ (this->modulo());
        Vector v= (*this) *q;
        return v;
      }




    private:
      double m_v[3];

};

//std::ostream &operator<<(std::ostream &stream, Vector v){
  //    stream << "(" << v.X() << "," << v.Y() << "," << v.Z() << ")";
    //   return stream;
//};


#endif