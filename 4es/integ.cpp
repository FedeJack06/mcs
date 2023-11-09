#include <iostream>
#include <cmath>

double fun(double x){
  return  pow(x,3);
}

//metodo dei trapezi (n=numero intervallini fissato)
double integN(double f(double),double a, double b, int n){
  double w   = (b-a)/n;
  double val = (f(a)+f(b))*w/2; //eq che evita ricalcolo estremi
  for (int i=1;i<n-1;i++){
    double x = a+w*i;
    val += w*f(x);
  }
  return val;
}

//cambio numero intervalli finche sono sotto precisione voluta
//eps = precisione 
double integPrec(double f(double),double a, double b, double eps){
  int n=2;
  double val0,val1 = integN(f,a,b,n);
  do {
    val0 = val1;
    val1 = integN(f,a,b,n*2); //raddoppio numero intervalli
    n = n*2;
  } while(fabs(val0-val1)>eps);//valuto se abbastanza preciso, fabs is abs
  return val1;
}

int main(){
  std::cout << integPrec(fun,0,1,0.00001) << std::endl;
  return 0;
}
