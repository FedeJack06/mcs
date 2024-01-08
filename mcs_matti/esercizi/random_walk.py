from ROOT import *
import numpy as np
import math as m
import matplotlib.pyplot as plt

N=3
rnd = TRandom3()
rnd.SetSeed(123456789)
ntot =np.array([20,30,40])

h=TH1D("h","titolo",50,0.,0.)
c=TCanvas()

d1=0
d2=0
d3=0

for i in range(0,20):
    d = 2*m.sqrt(3)*rnd.Rndm() - m.sqrt(3)
    d1= d1 + d
    
for i in range(0,40):
    d = 2*m.sqrt(3)*rnd.Rndm() - m.sqrt(3)
    d2=d2+d

for i in range(0,60):
    d = 2*m.sqrt(3)*rnd.Rndm() - m.sqrt(3)
    d3 =d3+d

d=np.array([d1,d2,d3])

plt.plot(d**2,ntot,"*")
plt.show()

for i in range(0,1000):
    d4=0
    for j in range(0,100):
        d= 2*m.sqrt(3)*rnd.Rndm() - m.sqrt(3)
        d4=d+d4
    h.Fill(d4)

c.Draw()
h.Draw("SAME")

gApplication.Run(True)

