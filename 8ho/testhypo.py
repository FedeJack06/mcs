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
h1.Draw("E")
h2.Draw("ESAME")
gApplication.Run(True)

# test del chi2

# test unbinned KS 2 campioni

# test unbinned KS 1 pdf

# test su esponenziale ignoto (con fit)




