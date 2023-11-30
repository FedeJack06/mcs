from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau):
    val = 0
    # Definisco logl
    for i in range(1, h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        timin = h.GetBinLowEdge(i)
        timax = timin + h.GetBinWidth(i)
        pi = exp(-timin/tau) -exp(-timax/tau)
        val = val - ni*log(pi)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2)
# Istruisco fir di logl
m.errordef = 0.5
m.print_level = 3
m.migrad()       

tau = m.values[0]
h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
f.SetParameter(1,tau)
f.Draw("SAME")

gApplication.Run(True)

