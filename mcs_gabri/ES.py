from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *


##-----------------------------------------------------##
##Istogramma e riempimento da file con un dato per riga##
##-----------------------------------------------------##
c = TCanvas()
c.Divide(2)
c.cd(1)
h  = TH1D("h","Distribuzione",50,0.,1.)
for line in open("data.dat"):
    h.Fill(float(line))

h.Draw()

## Fit 
f = TF1("f","[0]*x^([1]-1)*(1-x^[1])^([2]-1)",0.,1.)
f.SetParameter(1,2.5)
f.SetParameter(2,9)
f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1)) ##per normalizzazione
f.Draw('SAME')

##Fit Binned con Extended Maximun Likelihood
h.Fit('f','L')
gApplication.Run(True)

##Acquisizione parametri
a_T  = f.GetParameter(1)
b_T  = f.GetParError(2)
ea_T = f.GetParError(1)
eb_T = f.GetParError(2)

##Simulazione dell'esperimento per N = 1000
N = 1000 ##numero di ripetizioni dell'esperimento intero

##Estrazione con metodo di inversione MC per ogni N di 200 misure come nel file data.dat
n   = 200 ##numero eventi 
rnd = TRandom3()
rnd.SetSeed(123456789)

hab = TH2D("hab","Distribuzione 2D di a e b",70,0.,0.,70,0.,0.)

for i in range(0,N):
    hN = TH1D("h","Simulazione",50,0.,1.)
    ##Estrazioni
    for j in range(0,n):
        eta = rnd.Rndm()
        x = (1-(eta+1)**(1/b_T))**(1/a_T)
        hN.Fill(x)

    h.Fit('f','L')
    aN  = f.GetParameter(1)
    bN  = f.GetParError(2)
    eaN = f.GetParError(1)
    ebN = f.GetParError(2)
    hab.Fill(aN,bN)

c.cd(2)
hab.Draw()
print(hab.GetCorrelationFactor())



