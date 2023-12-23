from   sys   import *
from   math  import *
from   ROOT  import *
import numpy as np
from   scipy import stats


h1 = TH1D("h1","",40,0,0.5)
h2 = TH1D("h2","",40,0,0.5)

x1 = np.loadtxt("s1.dat")
x2 = np.loadtxt("s2.dat")
for i in range(len(x1)):
    h1.Fill(x1[i])
for i in range(len(x2)):
    h2.Fill(x2[i])

h1.SetLineColor(kRed)    
h2.SetLineColor(kBlue)
h1.Draw("E")
h2.Draw("ESAME")
gApplication.Run(True)

# test del chi2
print("Test chi1 (1/2) ", h1.Chi2Test(h2))#cambiando bin viene altro valore, ALTA VARIABILITÀ
print("Test chi2 (2/1) ", h2.Chi2Test(h1))

# test unbinned KS 2 campioni ##outuput statistica, pi-value
t_ks2, p_ks2 = stats.ks_2samp(x1, x2) #indip dal bin, dove utilizzabile (1D), più potente
print("test KS 2 samples ", p_ks2)

# test unbinned KS 1 pdf
#vuole una cumulativa
#expo con lamnda = 10
fun = stats.expon(loc=0.0, scale=0.1)
t_ks, p_ks = stats.kstest(x1, fun.cdf)
print("test KS (su s1)", p_ks)

#se 1 e 2 incompatibili, se faccio test sulla 2 il p-value dovrebbe venire incompatibile
t_ks, p_ks = stats.kstest(x2, fun.cdf)
print("test KS (su s2)", p_ks)

# test su esponenziale ignoto (con fit)
f = TF1("exp", "[0]/[1]*exp(-x/[1])")
f.SetParameter(1, 0.1)
f.SetParameter(2, h1.GetEntries()*h1.GetBinWidth(1))
h1.Fit("exp", "L")
chi2Newmann = h1.Chisquare(f, "N")
chi2BC = h1.Chisquare(f, "BC")
print("prob chi2N ", TMath.Prob(chi2Newmann, h1.GetNbinsX()-2))
print("prob chi2BC ", TMath.Prob(chi2BC, h1.GetNbinsX()-2))

gApplication.Run(True)


