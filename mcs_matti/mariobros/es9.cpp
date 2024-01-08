#include <TF1.h>
#include <iostream>

class myTF1:public TF1{
public:
  using TF1::TF1;

  double find_zero(double p,double N){
    double xsucc;
    double x;
    x=p;
    int i=0;
    while(i<N){
      xsucc= x - (*this).Eval(x)/(*this).Derivative(x);
      x=xsucc;
      i=i+1;
    }
    return xsucc;
  }
};

using namespace std;

int main(){
  myTF1 f("f","sin(x)",0,5);

  cout<<"boh "<<f.find_zero(3,1000) <<endl;
}
