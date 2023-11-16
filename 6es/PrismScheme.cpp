#include <iostream>
#include <cmath>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TApplication.h>

using namespace std;

namespace ex{
  double alpha   = M_PI/3;
  double lambda1 = 579.1;
  double lambda2 = 404.7;
  double th0   = 1.5701;
  double th1   = 2.6958;
  double th2   = 2.7904;
  double eth   = 0.0005;
}

void GetAB(double th0, double th1, double th2, double &A, double &B){
  //  A  = ..
  //  B  = ..
}

int main(){
  // Assumendo errore gaussiano (eth/sqrt(3)) 
  // a) calcolo dell'errore su A e su B tramite variazione delle funzione
  // b) calcolo delle distribuzioni di A e B
  //    dell'errore su A, B e della loro correlazione

  // Ripetere punto b) nel caso in cui invece si assuma distribuzione uniforme con larghezza +/-eth

  return 0;

}
