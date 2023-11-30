from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau):
    val = 0
    # Definisco logl
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2,norm=1000)
# Istruisco fir di logl
# m.migrad()       

# tau = m.values[0]
h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)

gApplication.Run(True)

