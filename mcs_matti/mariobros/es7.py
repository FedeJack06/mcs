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
