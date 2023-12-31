################################# ESERCITAZIONE 6
import math
import ROOT
import time


# Parametri dello spettrometro

# In[31]:


alpha   = math.pi/3
lambda1 = 579.1e-9
lambda2 = 404.7e-9
th0     = 1.5701
th1     = 2.6958
th2     = 2.7904
eth     = 0.0005


# Funzione che, dati gli angoli $\theta_0$, $\theta_1$ e $\theta_2$, calcola A e B

# In[37]:


def computeAB(th_0,th_1,th_2):
    def n_i(th_i, th_0):
        return math.sin((th_i - th_0 + alpha)/2)/math.sin(alpha/2)
    A = (n_i(th_1, th_0)*lambda1**2 - n_i(th_2, th_0)*lambda2**2)/(lambda1**2 - lambda2**2)
    B = (n_i(th_1, th_0) - n_i(th_2, th_0))/(1/(lambda1**2) - 1/(lambda2**2))
    return A, B


# In[33]:


computeAB(th0, th1, th2)[1]


# Programma principale

# In[34]:


eth_stat = eth/math.sqrt(3)
sigma = [0,0]
for i in range(2):
    f = computeAB(th0 , th1, th2)[i]
    sigma1 = computeAB(th0 + eth_stat, th1, th2)[i] - f
    sigma2 = computeAB(th0, th1 + eth_stat, th2)[i] - f
    sigma3 = computeAB(th0, th1, th2 + eth_stat)[i] - f
    sigma[i] = math.sqrt(sigma1**2 + sigma2**2 + sigma3**2)

print(sigma[0]) #errore A
print(sigma[1]) #errore B

# Assumendo errore gaussiano (eth/sqrt(3)) 
# a) calcolo dell'errore su A e su B tramite variazione delle funzione
# b) calcolo delle distribuzioni di A e B
#    dell'errore su A, B e della loro correlazione

# Ripetere punto b) nel caso in cui invece si assuma distribuzione uniforme con larghezza +/-eth


# In[55]:


rnd=ROOT.TRandom3()
rnd.SetSeed(int(time.time()))

Ntot = 10000
hA = ROOT.TH1D("histA", "distribuzione di A", 1000, 1.728, 1.732)
hB = ROOT.TH1D("histB", "distribuzione di B", 1000, 13.2e-15, 13.7e-15)
hAB = ROOT.TH2D("histAB", "Distrib A vs B", 1000, 1.728, 1.732, 1000, 13.2e-15, 13.7e-15)

for i in range (Ntot):
    AB_gauss = computeAB(rnd.Gaus(th0, eth_stat), rnd.Gaus(th1, eth_stat), rnd.Gaus(th2, eth_stat))
    hA.Fill(AB_gauss[0])
    hB.Fill(AB_gauss[1])
    hAB.Fill(AB_gauss[0], AB_gauss[1])

cA=ROOT.TCanvas()
cB=ROOT.TCanvas()
cAB=ROOT.TCanvas()
cA.Draw()
cA.cd()
hA.Draw()

cB.Draw()
cB.cd()
hB.Draw()

cAB.Draw()
cAB.cd()
hAB.Draw()


# In[45]:


hAB.GetCorrelationFactor()


# In[60]:


rnd=ROOT.TRandom3()
rnd.SetSeed(int(time.time()))

Ntot = 10000
hA = ROOT.TH1D("histA", "distribuzione di A", 1000, 0, 0)
hB = ROOT.TH1D("histB", "distribuzione di B", 1000, 0, 0)
hAB = ROOT.TH2D("histAB", "Distrib A vs B", 1000, 0,0, 1000, 0, 0)

for i in range (Ntot):
    AB_gauss = computeAB(rnd.Uniform(th0 - eth_stat, th0 + eth_stat), rnd.Uniform(th1 - eth_stat, th1 + eth_stat), rnd.Uniform(th2 - eth_stat, th2 + eth_stat))
    hA.Fill(AB_gauss[0])
    hB.Fill(AB_gauss[1])
    hAB.Fill(AB_gauss[0], AB_gauss[1])

cA=ROOT.TCanvas()
cB=ROOT.TCanvas()
cAB=ROOT.TCanvas()
cA.Draw()
cA.cd()
hA.Draw()

cB.Draw()
cB.cd()
hB.Draw()

cAB.Draw()
cAB.cd()
hAB.Draw()


# In[59]:
hAB.GetCorrelationFactor()


########################################################################
######################################ROBA UTILE
import ROOT
c=ROOT.TCanvas()
c.Divide(2,1)
c.Draw()
c.cd(1)
f1 = ROOT.TF1("f1","sin(x)/x",-10*ROOT.TMath.Pi(),10*ROOT.TMath.Pi())
f1.Draw()
c.cd(2)
f2 = ROOT.TF1("f2","TMath::Gaus(x,0,1)",-3,3)
f2.Draw()

#########################################################################
####################################### ES 8 (2 metodi da verificare)
{
  /*
   *
   *programma per l'utilizzo di mnemat che estrae la covarianza da un fit
   *
   */
  ifstream ifile("daties8.dat");
  TH1D *h=new TH1D("h","title",45,-1,1);
  
  /*funzione con relativo fattore di normalizzazione opportuno
   *ottenuto integrando nel dominio -1 1*/
  TF1 *f=new TF1("f","[2]*(1/(2+(2./3.)*[0]))*(1+[1]*x+[0]*x*x)",-1,1);

  double theta;
  //definizione di una matrice vuota 2x2, da utilizzare per mnemat
  double cov[3][3];

  while(ifile>>theta){
    h->Fill(theta);
  }   
  h->Draw();

  //f->FixParameter(2,1);
  f->FixParameter(2,h->GetEntries()*h->GetBinWidth(2));
  h->Fit("f","L");
  gMinuit->mnemat(&cov[0][0], 3);

  cout<<"correlazione "<<cov[0][1]/(f->GetParError(0)*f->GetParError(1))<<endl;

  double alpha =f->GetParameter(1);
  double ealpha=f->GetParError(1);
  double beta=f->GetParameter(0);
  double ebeta=f->GetParError(0);
  double gamma=3*alpha-2*beta;
  double egamma=sqrt(pow(3*ealpha,2)+pow(2*ebeta,2)+2*cov[0][1]*(-6));

  cout<<"miglior stima di gamma "<<gamma <<" +/- "<<egamma<<endl; 
 
}
##### METODO 2
{
  ifstream ifile("daties8.dat");

  double x=0;
  double cov[3][3];

  TH1D *h=new TH1D("h","titolo",40,-1,1);

  while(ifile>>x){
    h->Fill(x);
  }
  h->Draw();

  TF1 *f=new TF1("f","[0]*(1+[1]*x+[2]*x*x)",0.,0.);
  f->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
  f->SetParameter(1,1);
  f->SetParameter(2,3);

  h->Fit("f","L");

  gMinuit->mnemat(&cov[0][0],3);

  double a=f->GetParameter(1);
  double ea=f->GetParError(1);
  double b=f->GetParameter(2);
  double eb=f->GetParError(2);

  cout<<"parametri "<<a<<"+/- "<<ea<<" /-----/ "<<b<<"+/-"<<eb<<" correlazione "<< cov[2][1]/(ea*eb)<<endl;
  cout<<"p-value "<<f->GetProb()<<endl;
}

#############################################################################################
#########################################


