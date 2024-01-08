from   sys   import *
from   math  import *
from   ROOT  import *
import numpy as np
from   scipy import stats

file1 = open("s1.dat")
file2 = open("s2.dat")

h1 = TH1D("h1","",12,0,0.5)
h2 = TH1D("h2","",12,0,0.5)

x1 = np.array([])
for line in file1:
    val = line.split()
    x1 = np.append(x1,float(val[0]))
    h1.Fill(float(val[0]))

x2 = np.array([])
for line in file2:
    val = line.split()
    x2 = np.append(x2,float(val[0]))
    h2.Fill(float(val[0]))

h1.SetLineColor(kRed)    
h1.Draw("E")

h2.Draw("ESAME")


# test del chi2: BINNATO

p = h1.Chi2Test(h2);
print(p) #se < 0.05 rigettata ipotesi nulla non provengono quindi dalla stessa ditribuzione 

# test unbinned KS 2 campioni non binnato
D,P_ks = stats.ks_2samp(x1,x2)


print(P_ks) #anche con kolmogorov rigettiamo l'ipotesi in cui i dati seguono la stessa pdf

# test unbinned KS 1 pdf
e = stats.expon(loc=0, scale=0.1)
D1, p_ks1 = stats.kstest(x1,e.cdf)

print(p_ks1) #0.23 quindi l ipotesi h0 non puo essere rigettata: quinidi non possiamo dire che i nostri dati non seguono questa distribuzione



#in questo caso possiamo fare anche un fit di chi quadro perche in ogni bin abbiamo piu di 5 entrate, ma likelihood meglio: vediamo

# test su esponenziale ignoto (con fit)
f = TF1("exp","[0]/[1]*exp(-x/[1])",0,0.5);
f.SetParameter(1,1)



h1.Fit("exp")
print("P-value chi2: ", f.GetProb()) #o analogamente:
#print(TMath.Prob(f.GetChisquare(),h1.GetNbinsX()-2)) 0.95 quindi non poassiamo rigettare ipotesi che dati seguano esponenziale

h1.Fit("exp","L")
print("P-value likelihood: ", f.GetProb()) 

gApplication.Run(True)



