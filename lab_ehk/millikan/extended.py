from ROOT import *
from iminuit import Minuit
import numpy as np
from math import *

h = TH1D("h", "", 50, 0, 7)
for line in open("millikan.dat"):
    h.Fill(float(line))

h.Draw()

f = TF1("f", "[2]*TMath::Gaus(x, [0], [1], 1) + [3]*TMath::Gaus(x, 2*[0], [1], 1) + (1-[2]-[3])*TMath::Gaus(x, 3*[0], [1], 1)", 0, 7)
f.SetParameters(1.6, 1, 1, 1);

h.Fit("f", "L")

gApplication.Run(True)
