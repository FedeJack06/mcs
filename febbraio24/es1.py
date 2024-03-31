'''
Confrontare chi^2 Pearson e Neyman con distribuzione di chi^2 di una distribuzione uniforme fra [0,1]
1) generare N*Nbin eventi in modo da avere in ogni bin circa N conteggi
2) calcolare i chi quadri e ripere per N=1000 per ottenere le loro distribuzioni, sovrapporre gli istogrammi con la distrib di chi^2
3) ripetere 2) con N=5, 10, 100; cosa si conclude?
'''

from ROOT import *
import math

rnd = TRandom3()
rnd.SetSeed(123456789)

N = 1000
Nbin = 30

def unif(x):
    if x>=0 and x<=1:
        return N
    else:
        return 0

###############PUNTO 1
c0 = TCanvas("histo", "histo", 800, 500)
c0.cd()
histo = TH1D("histo","",Nbin,0.,1.2)
for i in range(N*Nbin): #N*Nbin eventi
    x = rnd.Rndm() #genero distrib uniforme
    histo.Fill(x)
histo.Draw()

hPearson = TH1D("pearson","",50,1000.,1060.)
hNeyman = TH1D("pearson","",50,830.,890.)

###############PUNTO 2
for j in range(10): #punto 2: 1000 volte e calcolo chi quadri
    h = TH1D("h","",Nbin,0.,1.2)
    for i in range(N*Nbin): #N*Nbin eventi
        x = rnd.Rndm() #genero distrib uniforme
        h.Fill(x)
    pearson = 0.0
    neyman = 0.0
    for u in range (1,30):
        if h.GetBinContent(u) != 0.0:
            pearson = pearson + (h.GetBinContent(u)-N)**2/N
            neyman = neyman + (h.GetBinContent(u)-N)**2/h.GetBinContent(u)
    print(pearson)
    print(neyman)
    hPearson.Fill(pearson)
    hNeyman.Fill(neyman)
c1 = TCanvas("p", "pearson", 800, 500)
c1.cd()
hPearson.Draw()
c2 = TCanvas("n", "neyman", 800, 500)
c2.cd()
hNeyman.Draw()

c1.cd()
chi = TF1("chi", "[0]*ROOT::Math::chisquared_pdf(x,30,[1])", 1000, 1100)
chi.FixParameter(0, hPearson.GetEntries()*hPearson.GetBinWidth(1))
chi.FixParameter(1, hPearson.GetMean())
chi.Draw("same")

c2.cd()
chi2 = TF1("chi2", "[0]*ROOT::Math::chisquared_pdf(x,30,[1])", 800, 900)
chi2.FixParameter(0, hNeyman.GetEntries()*hNeyman.GetBinWidth(1))
chi2.FixParameter(1, hNeyman.GetMean())
chi2.Draw("same")

gApplication.Run(True)
