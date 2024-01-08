from ROOT import *
import math as m

N=10000
rnd=TRandom3()
rnd.SetSeed(123456789)

h=TH1D("h","titolo",38,0.,0.)

mu=25

for j in range(0,N):
    s=0
    for i in range(0,N):
        dt= -m.log(1-rnd.Rndm())
        s=s+dt
        if s>mu:
            h.Fill(i-1)
            break
    
h.Draw()

f=TF1("f","[1]*TMath::Poisson(x,[0])")
f.SetParameter(1,1)
f.SetParameter(0,mu)

h.Fit("f","L")

print("maurizio ",f.GetProb())

gApplication.Run(True)
