#ifndef myTF1_H
#define myTF1_H
#include "TF1.h"
#include "TMath.h"

class myTF1: public TF1{
 public:
  using TF1::TF1;

  double NRzero(double N,double x0){
    double zero;
    //ordine 1    
    zero= x0 -((*this).Eval(x0))/((*this).Derivative(x0));
    //successivi
    for (int i=0;i<N;i++){
      zero= zero -((*this).Eval(zero))/((*this).Derivative(zero));
    }
    return zero;
  };
  
};

#endif

using namespace std;
  
int main(){
  myTF1 g=*new myTF1("g","TMath::Sin(x)",-100,100);

  double d=g.NRzero(100,(TMath::Pi()-1));

  cout<<"zero "<< d<<endl;
 }
