#include "Vector.h"
#include <cmath>

double Vector::X(){          // ha come unico obiettivo ritornare la 1 componente del vettore
    return m_v[0];
}

double Vector::Y(){         
    return m_v[1];
}

double Vector::Z(){          
    return m_v[2];
}

void Vector::X(double x){
    m_v[0]=x;
}
void Vector::Y(double y){
    m_v[1]=y;
}
void Vector::Z(double z){
    m_v[2]=z;
}

Vector Vector::operator+(Vector b){
    Vector s;
    for(int i=0;i<3;i++)
    s.m_v[i]= m_v[i] + b.m_v[i];
    return s;
}
//implemento il meno come operatore che cambia il segno al vettore sul quale viene usato
Vector Vector::operator-(){
    Vector m;
    for(int i=0;i<3;i++)
    m.m_v[i]= -m_v[i];
    return m;
}

Vector Vector::operator*(double k){
    Vector g;
    for(int i=0;i<3;i++)
    g.m_v[i]= m_v[i]*k;
    return g;
}

double Vector::operator*(Vector w){
    double sc=0;
    for (int i = 0; i < 3; i++)
    sc += m_v[i]*w.m_v[i];
    return sc;
}

Vector Vector::operator^(Vector r){
    Vector pv;
    pv.m_v[0]=m_v[1]*r.m_v[2]-m_v[2]*r.m_v[1];
    pv.m_v[1]=-m_v[0]*r.m_v[2]+m_v[2]*r.m_v[0];
    pv.m_v[2]=m_v[0]*r.m_v[1]-m_v[1]*r.m_v[0];
    return pv;
}

double Vector::modulo(){   
    double a;     
    a=(*this * *this);
        double b=sqrt(a);
        return b;
}

/*
double Vector::modulo(){
    double a=sqrt(m_v[0]*m_v[0]+m_v[1]*m_v[1]+m_v[2]*m_v[2]);
    return a;
}
*/
