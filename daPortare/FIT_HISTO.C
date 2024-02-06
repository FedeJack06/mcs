///////////////////// ES ESAME 3 - SPETTROGRAMMA
{
  ifstream ifile("Dati_Spettrometro.dat");
  double tmp;
  TH1D *histo = new TH1D("histo", "", 70, 0.555, 0.595);
  while(ifile >> tmp){
    histo->Fill(tmp);
  }
  histo->Draw();
  /*
  TF1 *gaus = new TF1("gaus", "[0]*TMath::Gaus(x,[1],[2])");
  gaus->SetParameter(0, histo->GetEntries()*histo->GetBinWidth(1));
  gaus->SetParameter(1, histo->GetMean());
  gaus->SetParameter(2, histo->GetRMS());
  histo->Fit("gaus", "L");//uso likehood perchè ho bin con freq < 5, no chi^2
  cout<<"p-value "<< gaus->GetProb() << endl;//valore < 0.05, rigetto gauss singola
  */
  TF1 *gaus2 = new TF1("gaus2", "[0]*([1]*TMath::Gaus(x,[2],[3]) +(1-[1])*TMath::Gaus(x, [4],[5]))");
  gaus2->SetParameter(0, histo->GetEntries()*histo->GetBinWidth(1));
  gaus2->SetParameter(2, 0.57);
  gaus2->SetParameter(3, 0.0001);
  gaus2->SetParameter(4, 0.582);
  gaus2->SetParameter(5, 0.0001);
  histo->Fit("gaus2", "L");
  cout<<"p-value "<< gaus2->GetProb() << endl;

  //calcolo A dalle due gaussiane
  double B=0.1, V=1e3; q=TMath::Qe();
  
  double d1 = gaus2->GetParameter(2);
  double m1 = (B*B*q/(2*V))*pow(d1/2, 2);
  double A1 = m1/1.66e-27;
  cout << "m1 :" << A1 << endl;

  double d2 = gaus2->GetParameter(4);
  double m2 = (B*B*q/(2*V))*pow(d2/2, 2);
  double A2 = m2/1.66e-27;
  cout << "m2 :" << A2 << endl;
}


///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// HANDS ON FIT I - FIT LIN - GLS
namespace data{
  vector<double>  x, y, ex, ey;
}

double fun(const double *x,const double *par){
  return par[1]*(*x)+par[0];
}

void fcn(int &npar,double *gin,double &f,double *par,int iflag){
  f = 0.0;
  for (int i=0;i<data::x.size();i++){
    f += pow(data::y[i]-fun(&data::x[i],par),2)/(pow(data::ey[i],2) + pow(par[1]*data::ex[i],2));
    // Calcolo del Chi2
  }
}

void fitlin(){
  ifstream file("pendolo.dat");
  double x,y,ex,ey;
  while (file >> x >> y >> ex >> ey){
    data::x.push_back(x); data::y.push_back(y); data::ex.push_back(ex); data::ey.push_back(ey);
  }

  // Define the minimization problem
  TMinuit *minuit = new TMinuit(2); // numero di parametri  
  minuit->SetFCN(fcn);
  //minuit->SetErrorDef(1.0);
  minuit->DefineParameter(0,"beta_0",0,0.01,0.0,0.0);
  minuit->DefineParameter(1,"beta_1",4,0.01,0.0,0.0);
  // per ogni indice inserisco nome, valore iniziale, step, minimo, massimo del parametro

  // Minimize
  minuit->Command("MIGRAD"); // Comando di minimizzazione //HESSE calcolo preciso matrice di covarianza
  //MINOS calcolo erorrori asim
  //trova solo il minimo, e i parametri, non disegna
  double beta0, beta1, ebeta0, ebeta1;

  // Get result
  minuit->GetParameter(0,beta0,ebeta0);
  minuit->GetParameter(1,beta1,ebeta1);
  // per ogni indice estraggo il valore del parametro e del suo errore
  // minuit->GetParameter(indice,val,eval);

}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////
from iminuit import Minuit
from numpy   import *
import matplotlib.pyplot as plt

def f(x,par):
    return par[1]*x+par[0]

def chi2(par):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],par))/ey[i])**2/(ey[i]**2 + (par[1]*ex[i])**2)
    return val

# Acquisizione dati
x,y,ex,ey = loadtxt('pendolo.dat',usecols=(0,1,2,3),unpack=True)

## Chiamo Minuit nella modalita' parametri passati tramite array
par = array([0, 4])
mn = Minuit(chi2,par)
mn.print_level = 4 #livello che mi da minuit sull'informazione
mn.migrad()
print("beta_0: %f +- %f "%(mn.values[0],mn.errors[0]))
print("beta_1: %f +- %f "%(mn.values[1],mn.errors[1]))
mn.draw_mnmatrix(cl=[1,2,3])
plt.show()

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////
from   iminuit import Minuit
from   numpy   import *
import matplotlib.pyplot as plt

def f(x,m,q):
    return m*x+q

def chi2(a,b): #m,q
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],a,b))/ey[i])**2
    return val

# Acquisizione dati
x,y,ex,ey = loadtxt('pendolo.dat',usecols=(0,1,2,3),unpack=True)
mn = Minuit(chi2, a=4, b=0)
mn.print_level = 3 #livello che mi da minuit sull'informazione
mn.migrad()
print("beta_0: %f +- %f "%(mn.values[0],mn.errors[0]))
print("beta_1: %f +- %f "%(mn.values[1],mn.errors[1]))
mn.draw_mnmatrix(cl=[1,2,3])
plt.show()

## Chiamo Minuit nella modalita' parametri passati tramite passaggio dei singoli parametri
## Esplorare la funzione draw_mnmatrix per fare i contour

///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// SIMPLE FIT + CONTOUR
{
  TGraphErrors *gr = new TGraphErrors("pendolo.dat");
  TF1 *f = new TF1("f","[1]*x+[0]");
  f->SetParameter(0,4);
  f->SetParameter(1,0);
  gr->Draw("AP");
  // Correlation matrix
  auto ptr = gr->Fit("f","S");
  auto cov = ptr->GetCovarianceMatrix();
  cov.Print();
  auto cor = ptr->GetCorrelationMatrix();
  cor.Print();
  
  // Band
  gMinuit->SetErrorDef(1);
  auto grc = (TGraph*)gMinuit->Contour(10,0,1); //cast di tobject
  grc->Draw("AC");
  // Contour
}  


/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// KATER FIT SIMULTANEO
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>

using namespace std;

namespace data{
  int n;
  vector<double> x1,t1,et1;
  vector<double> x2,t2,et2;
}

TF1 *f1;
TF1 *f2;

void chi2(int &npar, double *gin, double &f, double *par, int iflag){
  f=0;
  f1->SetParameter(0,par[0]);
  f1->SetParameter(1,par[1]);//f1 e f2 stessa intersezione
  f1->SetParameter(2,par[2]);
  f2->SetParameter(0,par[0]);
  f2->SetParameter(1,par[1]);
  f2->SetParameter(2,par[4]);

  f1->SetParameter(3,par[3]);
  f2->SetParameter(3,par[5]);

  for (int i=0; i<data::x1.size(); i++)
    f += pow(data::t1[i]-f1->Eval(data::x1[i]),2)/pow(data::et1[i],2);
  for (int i=0; i<data::x2.size(); i++)
    f += pow(data::t2[i]-f2->Eval(data::x2[i]),2)/pow(data::et2[i],2);
}


int main(){

  TApplication app("app",0,NULL);

  ifstream fp1("perno1.dat");
  ifstream fp2("perno2.dat");
  double tx1,tt1,tex1,tet1;
  double tx2,tt2,tex2,tet2;


  TGraphErrors gr1;
  while (fp1 >> tx1 >> tt1 >> tex1 >> tet1){
    data::x1.push_back(tx1);
    data::t1.push_back(tt1);
    data::et1.push_back(tet1);
    gr1.SetPoint(gr1.GetN(),tx1,tt1);
    gr1.SetPointError(gr1.GetN()-1,tex1,tet1);
  }

  TGraphErrors gr2;
  while (fp2 >> tx2 >> tt2 >> tex2 >> tet2){
    data::x2.push_back(tx2);
    data::t2.push_back(tt2);
    data::et2.push_back(tet2);
    gr2.SetPoint(gr2.GetN(),tx2,tt2);
    gr2.SetPointError(gr2.GetN()-1,tex2,tet2);
  }
  data::n=data::x1.size();

  f1 = new TF1("f1","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);
  f2 = new TF1("f2","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);

  gr1.Fit("f1");
  gr2.Fit("f2");
  gr1.Draw("AP");
  gr2.Draw("P");
  app.Run(true);

  // Minuit
  TMinuit mn(6);
  mn.SetFCN(chi2);
  mn.DefineParameter(0, "x0", 35, 0.01, 0.0, 0.0);
  mn.DefineParameter(1, "T0", 4, 0.01, 0.0, 0.0);
  mn.DefineParameter(2, "a1", f1->GetParameter(2), 0.01, 0.0, 0.0);
  mn.DefineParameter(3, "b1", f1->GetParameter(3), 0.01, 0.0, 0.0);
  mn.DefineParameter(4, "a2", f2->GetParameter(2), 0.01, 0.0, 0.0);
  mn.DefineParameter(5, "b2", f2->GetParameter(3), 0.01, 0.0, 0.0);

  mn.Migrad();
  double pout[6];
  /*for (int i=0; i<6; i++)
    mn.GetParameter(i,pout[i]);*/
  
  app.Run(true);

  return 0;

}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// HANDS ON FIT II - LIKEHOOD
namespace data{
  vector<double>  x;
}

void logl(int &npar, double *gin, double &f, double *par, int iflag){
  f = 0.0;
  // Definisco la logl, log(L)
  for(int i=0; i< data::x.size(); i++){
    f += log(par[0]) + data::x[i]/par[0];
  }
  
}

void fitexp(){

  ifstream file("exp.dat");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    data::x.push_back(x);
    h->Fill(x);
  }
  TMinuit minuit(1);
  minuit.SetFCN(logl);
  // Istruisco di logLikelihood
  minuit.SetErrorDef(0.5);
  minuit.DefineParameter(0,"tau",2,0.01,0.,0.);
  
  minuit.Command("MIGRAD");//"S" usa l'essiano, "MINOS" una il metodo grafico importante qua errorDef
  double tau, etau;
  minuit.GetParameter(0,tau,etau);

  h->SetMarkerStyle(20);
  h->Draw("E");
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);//[0] fattore di normalizzazione
  // Disegno della funzione
  //fisso valore tau
  fe->SetParameter(1, tau);
  //cambiare la normalizzazione altrimenti incoerenti con l'istogramma
  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(1));
  fe->Draw("same");
}

//////////////////////////////////////////////////////////////////////////
///////////////////////////////////// BINNED
from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau):
    val = 0
    # Definisco logl
    for i in range(1, h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        timin = h.GetBinLowEdge(i)
        timax = timin + h.GetBinWidth(i)
        pi = exp(-timin/tau) -exp(-timax/tau)
        val = val - ni*log(pi)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2)
# Istruisco fir di logl
m.errordef = 0.5
m.print_level = 3
m.migrad()       

tau = m.values[0]
etau = m.errors[0]
print(tau)
print(etau)

h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
f.SetParameter(1,tau)
f.Draw("SAME")

gApplication.Run(True)

f2 = TF1("f2","[0]*1/[1]*exp(-x/[1])",0,20)
f2.SetLineColor(4)
f2.FixParameter(0,1.)
f2.SetParameter(1,2.)

#uso metodo fit dell'isto
h.Fit("f2", "0MULTI") #0 per disegnare

f2.SetParameter(0, h.GetEntries()*h.GetBinWidth(1))
f2.Draw("SAME")

gApplication.Run(True)

  ////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////BINNED EXTENDED
from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau, norm):
    val = 0
    # Definisco logl
    for i in range(1, h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        timin = h.GetBinLowEdge(i)
        timax = timin + h.GetBinWidth(i)
        pi = exp(-timin/tau) -exp(-timax/tau)
        mui = norm*pi
        val = val - (ni*log(mui) - mui)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2,norm=1000)
# Istruisco fir di logl
m.errordef = 0.5
m.print_level = 3
m.migrad()       

tau = m.values[0]
etau = m.errors[0]
norm = m.values[1]
enorm = m.errors[1]

print(tau)
print(etau)
print(norm)
print(enorm)

h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(0,norm*h.GetBinWidth(1))
f.SetParameter(1,tau)

f.Draw("SAME")

gApplication.Run(True)

f2 = TF1("f2","[0]*1/[1]*exp(-x/[1])",0,20)
f2.SetLineColor(4)
f2.SetParameter(0,1000)
f2.SetParameter(1,2.)

#uso metodo fit dell'isto
h.Fit("f2", "0L") #0 per disegnare
normm = f2.GetParameter(0)

f2.SetParameter(0, normm)
f2.Draw("SAME")

#gSystem.ProcessEvents()
gApplication.Run(True)

/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// FIT MINOS
namespace data{
  vector<double>  x;
}

void logl(int &npar, double *gin, double &f, double *par, int iflag){
  f = 0.0;
  // Definisco la logl, log(L)
  for(int i=0; i< data::x.size(); i++){
    f += log(par[0]) + data::x[i]/par[0];
  }
  
}

void fitexp_Minos(){

  ifstream file("exp.dat");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    data::x.push_back(x);
    h->Fill(x);
  }
  TMinuit minuit(1);
  minuit.SetFCN(logl);
  // Istruisco di logLikelihood
  minuit.SetErrorDef(0.5);
  minuit.DefineParameter(0,"tau",2,0.01,0.,0.);
  
  minuit.Command("MINOS");//"S" usa l'essiano, "MINOS" una il metodo grafico importante qua errorDef
  double tau, etau;
  minuit.GetParameter(0,tau,etau);

  h->SetMarkerStyle(20);
  h->Draw("E");
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);//[0] fattore di normalizzazione
  // Disegno della funzione
  //fisso valore tau
  fe->SetParameter(1, tau);
  //cambiare la normalizzazione altrimenti incoerenti con l'istogramma
  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(1));
  fe->Draw("same");
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// FIT UNBINNED TTREE
namespace data{
  vector<double>  x;
}

void logl(int &npar, double *gin, double &f, double *par, int iflag){
  f = 0.0;
  // Definisco la logl, log(L)
  for(int i=0; i< data::x.size(); i++){
    f += log(par[0]) + data::x[i]/par[0];
  }
  
}

void fitexp_Tree(){

  ifstream file("exp.dat");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    h->Fill(x);
  }
  TTree *t = new TTree();
  t->ReadFile("exp.dat", "t/D");
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  fe->FixParameter(0, 1.);
  fe->SetParameter(1, 2.);
  t->UnbinnedFit("fe", "t");

  h->SetMarkerStyle(20);
  h->Draw("E");
  // Disegno della funzione
  //cambiare la normalizzazione altrimenti incoerenti con l'istogramma
  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(1));
  fe->Draw("same");
}

////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// ES 4 ESAMI
//altro modo di farlo senza usare tminuit ma solo likelihood
//non funziona, in questo caso andava meglio l'altro
{
  TH1D *h=new TH1D("h","",25,0.,0.);

  ifstream ifile("DatiGamma.dat");
  
  double a;
  while(ifile>>x){
    h->Fill(a);
  }

  h->Draw();

  TF1 *f=new TF1("f","[1]*((pow(x,2)*exp(-x/[0]))/(2*pow([0],3)))",0,30);
  f->FixParameter(1,224);
  f->FixParameter(0,pow(5.74,1/3));
  
  f->SetParameter(1,h->GetBinWidth(1)*h->GetEntries());
  
  h->Fit("f","L");


  cout<<f->GetParameter(0)<<endl;

}
/////////// CON PYTHON
from ROOT import*

x=0

file = open("DatiGamma.dat","r")

h= TH1D("h","titolo",40,0.,0.)

for x in file:
    h.Fill(float(x))

h.Draw()

#t=TTree()
#t.ReadFile("DatiGamma.dat","t/D")


f=TF1("f","[0]*((x**2*exp(-x/[1]))/2*[1]**3)",0.,0.)

f.SetParameter(0,1)
f.SetParameter(1,5.74/3)

#t.UnbinnedFit("f","t")

h.Fit("f","L")

print("theta ",f.GetParameter(1),"p-value ",f.GetProb())

    
gApplication.Run(True)

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// ES 7 fatto in due modi (da verificare)
import numpy as np
import math as m

from ROOT import *

rnd = TRandom3()

rnd.SetSeed(123456789)

x_0 = 10
sigma = 2
delta = 2

error = m.sqrt(sigma*sigma +delta*delta/3)

h = TH1D("h","",30,0.,0.)

for i in range(0,1000):
    #genero prima x' ed attorno costruisco una gaussiana per x
    x_primo = rnd.Gaus(10,2)

    #genero e poi prendo solo i punti che mi interessano spostando la distribuzione
    x = 2*delta*rnd.Rndm() + (x_primo - delta)
    
    h.Fill(x)

h.Draw()

f =TF1("f","[0]*TMath::Gaus(x,[1],[2])",0.,0.)
f.FixParameter(1,x_0)
f.FixParameter(2,error)

h.Fit("f","LL")
print("p-value ",f.GetProb())

gApplication.Run(True)



#viene p value 0.34 quindi 34% probabilita di ottenere dati peggiori dei miei
#il che è abbastanza alto (sarebbe al massimo opportuno ottenere 5%)

/////////////METODO 2

from ROOT import *
import math as m

N=1000
rnd=TRandom3()
rnd.SetSeed(123456789)

h=TH1D("h","titolo",40,0.,0.)

x0=10
sigma=2
delta=2
error= m.sqrt(sigma**2+(delta**2)/3)

for i in range(0,N):
    x_primo=rnd.Gaus(x0,sigma)

    x= (rnd.Rndm())*delta + x_primo

    h.Fill(x)

h.Draw()

f=TF1("f","[0]*TMath::Gaus(x,[1],[2])",0.,0.)
f.SetParameter(0,1)
f.SetParameter(1,x0)
f.SetParameter(2,error)

h.Fit("f","L")

print("p-value ",f.GetProb())

gApplication.Run(True)

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////


