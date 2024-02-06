from ROOT import *
import math

rnd = TRandom3()
rnd.SetSeed(123456789)

xzero = 10
sigma = 2
delta = 2
h = TH1D("h","",30,0.,0.)
for i in range(1000):
    x_primo = rnd.Gaus(xzero, sigma)
    x = rnd.Rndm()*(x_primo+delta - x_primo-delta) + x_primo-delta
    h.Fill(x)
h.Draw()

f =TF1("f","[0]*TMath::Gaus(x,[1],[2])")
f.FixParameter(1,xzero)
f.FixParameter(2, delta/sqrt(3))
f.SetParameter(0, h.GetEntries()*h.GetBinWidth(1))
h.Fit("f","LB") #B option for fix parameter in pre defined function (Gaus)

print("p-value :",f.GetProb()) #spiler: no

gApplication.Run(True)