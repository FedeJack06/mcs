##**********##
##HANDS ON 1##
##**********##

##*******************************************************##
##PROGRAMMA 1: testo a disposizione su aulaweb           ##
##SIMULAZIONE DI UN PROCEDIMENTO CON DUE POSSIBILI EVENTI##
##*******************************************************##
from ROOT import *
import math as m

##Si istanzia oggetto di TRandom3
rnd = TRandom3()
##Si setta il seme della sequenza di numeri pseudo-casuali
rnd.SetSeed(123456789)

##Numero di eventi e parametri in gioco
nev    = 10000
tau1   = 0.1
tau2   = 1
tauacc = 0.1 ## tau di accettazione, se si aumenta si vede piu' differenza perche' ne vedo meno: ci vuole piu' tempo perche' veda
ris    = 0.1 ##extra: risoluzione temporale; come genero per ogni tempo il tempo che mi aspetto di misurare se larghezza gaussiana che lega costruit             ##o a generato con larghezza ris?
f      = 0.3

h  = TH1D("h","",100,0,5) ##per valori casuali generati, l'esponenziale bastano 2 o 3 tau perche' a zero
hm = TH1D("hm","",100,0,5) ##per valori di tempo misurati (m) dallo strumento, parte due dell'esercizio
hr = TH1D("hr","",100,0,5) ##extra: tempo ricostruito 
for i in range(0,nev):
    if rnd.Rndm()<f: ## Siamo in caso 1
        t = -tau1*m.log(1-rnd.Rndm())
    else: ## Siamo in caso 2
        t = -tau2*m.log(1-rnd.Rndm())
    h.Fill(t)
    if rnd.Rndm()<(1-exp(-t/tauacc)): ##sono nella parte di successo sotto epsilon!!
        hm.Fill(t)
        tr = rnd.Gaus(t,ris) ## vuole centro e sigma
        #tr = t + rnd.Gaus(0,ris) ##Stesso oggetto di prima
        hr.Fill(tr)##extra: t ricostruito e' distribuito secondo gaussiana intorno t
    
    
h.Draw()
hm.Draw("SAME")
hm.SetLineColor(kRed)
hr.Draw("SAME")
hr.SetLineColor(kMagenta)
#gPad.SetLogy() ## per vedere le due rette: vi e' retta per esponenziale piccolo in alto, raccordo,retta esponenziale lungo dopo
gApplication.Run(True)


##********************************************##
##PROGRAMMA 2: testo a disposizione su aulaweb##
##CALCOLO DI VOLUMI (INTEGRALI)               ##
##********************************************##
from ROOT import *
import math as m

##Si istanzia oggetto di TRandom3
rnd = TRandom3()
##Si setta il seme della sequenza di numeri pseudo-casuali
rnd.SetSeed(123456789)

##Numero eventi e parametri in gioco
n = 1000000
R = 1
r=R/2

##Contatori
nsph = 0.
ni = 0.
##Generazione
for i in range(0,n):
    x = 2*R*rnd.Rndm()-R ##centrato in origine
    y = 2*R*rnd.Rndm()-R ##centrato in origine
    z = 2*R*rnd.Rndm()-R ##centrato in origine
    if x*x+y*y+z*z<R*R:
        nsph = nsph+1
        if x*x+y*y>r*r:
            ni = ni +1

##Probabilita' numero nella sfera cava o nel cilindro (processo binomiale e relativo calcolo d'errore)
p = nsph/n
ep = sqrt(p*(1-p)/n)

pi = ni/n
epi = sqrt(pi*(1-pi)/n)

##Volume proporzionale alla regione di generazione mediante p e pi e volume teorico
print("Volume Sfera (MC) %f +/- %f " %(p*(2*R)**3, ep*(2*R)**3))
print("Volume Sfera %f " %(4/3.*m.pi*(R)**3))

print("Volume Sfera bucata (MC) %f +/- %f " %(pi*(2*R)**3, epi*(2*R)**3))

##Volume cavo con cilindro: prendere lontano da z, piu' del raggio del cilindro
