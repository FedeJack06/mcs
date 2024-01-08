from ROOT import *

a=0.01
eps=0.1

while(abs((1/(1+eps))-(1/(1-eps)))>a):
      eps=eps/2

print(eps)
ntot=100000
rnd=TRandom3()
rnd.SetSeed(123456789)

h=TH1D("h","",50,0.,0.)
f=TF1("f","[0]*exp(-((x-[1])/[2])**2)",0.,0.)
f.SetParameter(0,8200)
f.SetParameter(1,1)
f.SetParameter(2,2*eps)

for i in range(0,ntot):
    h.Fill(1/(rnd.Gaus(1,2*eps)))

h.Draw()
h.Fit("f","L")

f.SetParameter(1,h.GetMean())
f.SetParameter(2,h.GetRMS())
f.Draw("SAME")

print("p-value ",f.GetProb())

gApplication.Run(True)
