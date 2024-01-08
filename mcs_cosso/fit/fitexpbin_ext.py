from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau,norm):
    val = 0
    # Definisco logl
    for i in range(1,h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        xmin = h.GetBinLowEdge(i)
        xmax = h.GetBinLowEdge(i)+h.GetBinWidth(1)
        pi = exp(-xmin/tau)-exp(-xmax/tau)
        mui = pi * norm #norm è un parametro da trovare
        val = val - (ni*log(mui)-mui)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2,norm=1000)
m.errordef = 0.5
m.print_level = 2
# Istruisco fir di logl
m.migrad()       


h.Draw("E")
tau = m.values[0]
norm = m.values[1]
print(tau)
# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(1, tau)
f.SetParameter(0,norm*h.GetBinWidth(1))
f.Draw("SAME")

h.Fit("f" , "L") #L perche si usa L per extended likelihood, inoltre non è necessario che f sia pdf dopo poiche in extended likelihood la normalizzazione è un parametro.

gApplication.Run(True)

