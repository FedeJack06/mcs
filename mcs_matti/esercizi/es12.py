from ROOT import*
import math as m
import numpy as np
from scipy import stats

N=100000
rnd=TRandom3()
rnd.SetSeed(123456789)
h=TH1D("h","titolo",38,7,44)
x=np.array([])

mu=25

for j in range(0,N):
    s=0
    for i in range(0,N):
        dt= -m.log(1-rnd.Rndm())
        s=s+dt
        if s>mu:
            h.Fill(i-1)
            x = np.append(x,i-1)
            break

h.Draw()

f=TF1("f","[0]*TMath::Poisson(x,[1])",0.,0.)
f.FixParameter(0,1)
f.SetParameter(1,mu)

f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
h.Fit("f","L")

print(f.GetProb())


#f.Draw("SAME")

gApplication.Run(True)

