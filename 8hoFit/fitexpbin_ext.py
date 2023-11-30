from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau, norm):
    val = 0
    # Definisco logl
    for i in range(1, h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        timin = h.GetBinLowEdge(i)
        timax = timin + h.GetBinWidth(i)
        pi = exp(-timin/tau) -exp(-timax/tau)
        mui = norm*pi
        val = val - (ni*log(mui) - mui)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2,norm=1000)
# Istruisco fir di logl
m.errordef = 0.5
m.print_level = 3
m.migrad()       

tau = m.values[0]
etau = m.errors[0]
norm = m.values[1]
enorm = m.errors[1]

print(tau)
print(etau)
print(norm)
print(enorm)

h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(0,norm*h.GetBinWidth(1))
f.SetParameter(1,tau)

f.Draw("SAME")

gApplication.Run(True)

f2 = TF1("f2","[0]*1/[1]*exp(-x/[1])",0,20)
f2.SetLineColor(4)
f2.SetParameter(0,1000)
f2.SetParameter(1,2.)

#uso metodo fit dell'isto
h.Fit("f2", "0L") #0 per disegnare
normm = f2.GetParameter(0)

f2.SetParameter(0, normm)
f2.Draw("SAME")

#gSystem.ProcessEvents()
gApplication.Run(True)

