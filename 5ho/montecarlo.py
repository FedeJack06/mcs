import ROOT
import math

rnd = ROOT.TRandom3()
rnd.SetSeed(165786865)

f = 0.3
tau1 = 0.1
tau2 = 1

Ntot =  10000
#100 bin, exp veloce e exp lento => metto 0.5 per presentare bene entrambi
h = ROOT.TH1D("hist","tempi di decadimento",100,0,5)
for i in range(0, Ntot, 1): #i++
    #p(t) divisa in due naturalmente
    #processo binomiale, controllo se atomo della sostanza 1 o 2
    if rnd.Rndm()<f:
        #sono in sostanza 1
        t = -tau1*math.log(rnd.Rndm())
    else:
        #sono in sostanza 2
        t = -tau2*math.log(rnd.Rndm())
    h.Fill(t)
h.Draw()
ROOT.gApplication.Run(True)
