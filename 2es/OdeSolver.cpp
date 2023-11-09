#include "Vector3.h"
#include "OdeSolver.h"

void OdeSolver::AddMatPoint(MatPoint tmp){
  m_p.push_back(tmp);
}

vector<MatPoint> OdeSolver::GetMatPoints(){
  return m_p;
}

MatPoint OdeSolver::GetMatPoint(unsigned int i){
  return m_p[i];
}

unsigned int OdeSolver::N(){
  return m_p.size();
}

void OdeSolver::T(double t0){
  m_t=t0;
}

double OdeSolver::T(){
  return      m_t;
}

void OdeSolver::DeltaT(double h){
  m_h = h;
}

double OdeSolver::DeltaT(){
  return   m_h;
}

Vector3 OdeSolver::m_A(unsigned int i, double t, vector<MatPoint> p){
  //STEP 3 Calcolo dell'accelerazione dovuta a forze interne e forze esterne
  //Sommo le forze interne dovute a tutti i MatPoint con indice j diverso da i
  Vector3 F_tot;
  for(unsigned int k=0; k < p.size() && k != i; k++){ 
    F_tot = F_tot + fInternal(i, k, 0, p);
  }
  //Sommo la forza esterna su i
  //Ritorno l'accelerazione
  return F_tot * (1/p[i].Mass());
}

//Da implementare a cura dello studente
void OdeSolver::Step(){

  if (m_method=="Eulero"){
    //x(t0 + h) = x(t0) + hx'(t0)
    vector<Vector3>  k1(m_p.size());
    vector<Vector3>  w1(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){ //m_p vector di matpoint
      k1[i] = m_h * m_p[i].V();     //h*x' = h*v  step di x0 di i in dt=h
      w1[i] = m_h * m_A(i,m_t,m_p); //h*v'  = h*a step di v0 di i in dt=h
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);  //aggiungo a x0 l'incremento in dt=h
      m_p[i].V(m_p[i].V() + w1[i]);  //aggiungo a v0 l'incremento in dt=h
    }

  } else if (m_method=="Rk2"){
    //x(t0 + h) = x(t0) + hx'(t0 + h/2) più preciso
    //calcolo la derivata a metà step
    //incrmento valori di uno step con la derivta di metà step
    vector<Vector3>  k1(m_p.size());
    vector<Vector3>  w1(m_p.size());

    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h * m_p[i].V();     //incremento di x0 in intervallo h
      w1[i] = m_h * m_A(i,m_t,m_p); //incremento di v0 in intervallo h
    }

    vector<MatPoint>  m_p2(m_p);;     //vettore con i in t0 + h/2
    for (unsigned int i=0;i<m_p.size();i++){
      m_p2[i].R(m_p2[i].R() + k1[i]*0.5);  //Pos += k1/2 avanzo di metà incremento
      m_p2[i].V(m_p2[i].V() + w1[i]*0.5);  //Vel += k1/2 avanzo di metà incrmento
    }

    vector<Vector3>  k2(m_p.size());
    vector<Vector3>  w2(m_p.size());
    for (unsigned int i=0; i<m_p.size(); i++){
      k2[i] = m_h * m_p2[i].V();        //incremento di x0 in dt = h con x'(t0 + h/2)  
      w2[i] = m_h * m_A(i, m_t + m_h/2, m_p2);  //incremento di v0 in dt = h cn v'(t0 + h/2)
    }
    
    for (unsigned int i=0; i<m_p.size(); i++){
      m_p[i].R(m_p[i].R() + k2[i]);  //Pos_i += k2 incremento in dt=h corretto
      m_p[i].V(m_p[i].V() + w2[i]);  //Vel_i += w2
    }
    
  } else if (m_method=="Rk4"){
    vector<Vector3>  k1(m_p.size());
    vector<Vector3>  w1(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h * m_p[i].V();     //incremento di x0 in intervallo h
      w1[i] = m_h * m_A(i,m_t,m_p); //incremento di v0 in intervallo h
    }

    vector<MatPoint>  m_p2(m_p);; 
    for (unsigned int i=0;i<m_p.size();i++){
      m_p2[i].R(m_p2[i].R() + k1[i]*0.5);  //posizione a metà incremento k1
      m_p2[i].V(m_p2[i].V() + w1[i]*0.5);  //velocità a metà incrmento w1
    }

    vector<Vector3>  k2(m_p.size());
    vector<Vector3>  w2(m_p.size());
    for (unsigned int i=0; i<m_p.size(); i++){
      k2[i] = m_h * m_p2[i].V();        //incremento di x0 in dt = h con v di p2  
      w2[i] = m_h * m_A(i, m_t + m_h/2, m_p2);  //incremento di v0 in dt = h con a di p2
    }

    vector<MatPoint> m_p3(m_p);
    for (unsigned int i=0; i<m_p.size(); i++){
      m_p3[i].R(m_p3[i].R() + k2[i]*0.5);  //pos a metà incremento k2 (2 ordine)
      m_p3[i].V(m_p3[i].V() + w2[i]*0.5); 
    }

    vector<Vector3>  k3(m_p.size());
    vector<Vector3>  w3(m_p.size());
    for (unsigned int i=0; i<m_p.size(); i++){
      k3[i] = m_h * m_p3[i].V();        //incremento di x0 in dt = h con v a metà k2  
      w3[i] = m_h * m_A(i, m_t + m_h/2, m_p3);  //incremento di v0 in dt = h cn ac a metà k2
    }

    vector <MatPoint> m_p4(m_p);
    for (unsigned int i=0; i<m_p.size(); i++){
      m_p4[i].R(m_p4[i].R() + k3[i]);  //pos di x0 in dt=h a fine incremento k3
      m_p4[i].V(m_p4[i].V() + w3[i]);
    }

    vector<Vector3>  k4(m_p.size());
    vector<Vector3>  w4(m_p.size());
    for (unsigned int i=0; i<m_p.size(); i++){
      k4[i] = m_h * m_p4[i].V();        //incremento di x0 in dt = h con v(x0 +k3)  
      w4[i] = m_h * m_A(i, m_t + m_h, m_p4);  //incremento di v0 in dt = h cn a(v0+ k3)
    } //guardo le derivate a fine incremento k3
    
    for (unsigned int i=0; i<m_p.size(); i++){
      m_p[i].R(m_p[i].R() + (1./6.)*k1[i] + (1./3.)*k2[i] + (1./3.)*k3[i] + (1./6.)*k4[i]);
      m_p[i].V(m_p[i].V() + (1./6.)*w1[i] + (1./3.)*w2[i] + (1./3.)*w3[i] + (1./6.)*w4[i]);
    }
  }
  m_t += m_h;
}

