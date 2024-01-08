import numpy as np
import math as m

from ROOT import *

rnd = TRandom3()

rnd.SetSeed(123456789)

x_0 = 10
sigma = 2
delta = 2

error = m.sqrt(sigma*sigma +delta*delta/3)

h = TH1D("h","",30,0.,0.)

for i in range(0,1000):
    #genero prima x' ed attorno costruisco una gaussiana per x
    x_primo = rnd.Gaus(10,2)

    #genero e poi prendo solo i punti che mi interessano spostando la distribuzione
    x = 2*delta*rnd.Rndm() + (x_primo - delta)
    
    h.Fill(x)

h.Draw()

f =TF1("f","[0]*TMath::Gaus(x,[1],[2])",0.,0.);
f.FixParameter(1,x_0)
f.FixParameter(2,error)

h.Fit("f","LL")
print("p-value ",f.GetProb())

gApplication.Run(True)



#viene p value 0.34 quindi 34% probabilita di ottenere dati peggiori dei miei
#il che è abbastanza alto (sarebbe al massimo opportuno ottenere 5%)
