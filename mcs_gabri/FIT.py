##**************##
##HANDS ON 2 E 3##
##**************##

##**********##
##HANDS ON 2##
##**********##

##********************************************************************************************************************##
##PROGRAMMA 1: SCOMODO, usare analogo PROGRAMMA 1 in FIT.C                                                            ##
##MINIMIZZAZIONE DELLA FUNZIONE FCN DI CHI2 A PARTIRE DA UNA FUNZIONE FUNC LINEARE NEI PARAMETRI CON PACCHETTO TMinuit##
##********************************************************************************************************************##
from   ROOT    import *
import numpy   as np
import ctypes  as ct

##Funzione di fit lineare nei parametri: funzione TF1 da fittare come al primo anno 
def func(x,a,b): 
    return a*x+b

##Funzione da minimizzare cin TMinuit: f e' chi2; classico chi2 da definizione con la funzione di TF1 specificata
def fcn(npar, gin, f, par,iflag):
    chi2 = 0.0
    for i in range(0,len(x)):
        chi2 += ((y[i]-func(x[i],par[0],par[1]))/ey[i])**2
    f.value = chi2

##----##
##MAIN##
##----##

##Lettura del file di dati e salvataggio degli stessi in array
x  = np.array([]); y  = np.array([]); ex = np.array([]); ey = np.array([])
for line in open("pendolo.dat"):
    dt  = line.split() ##divisione della riga in una lista
    if len(dt)!=4:     ##se la lista non e' divisa in 4 (dati), il dato non e' accettato
        continue
    ##Si converte da stringa a float e si riempono i vettori di numpy
    x   = np.append(x,  float(dt[0])); y   = np.append(y,  float(dt[1]))
    ex  = np.append(ex, float(dt[2])); ey  = np.append(ey, float(dt[3]))

##Si istanzia oggetto TMinuit con numero di parametri
minuit = TMinuit(2)
##Si istanzia la funzione da minimizzare
minuit.SetFCN(fcn);
##Si definiscono i parametri
minuit.DefineParameter(0,'par0',4,0.01,0.,0.)
minuit.DefineParameter(1,'par1',0,0.01,0.,0.)
##Comando di minimizzazione
minuit.Command("MIGRAD")
##Definizione scomoda dei parametri tramite variabili di C
a  = ct.c_double(0.0); b  = ct.c_double(0.0)
ea = ct.c_double(0.0); eb = ct.c_double(0.0)
##Presa dei parametri
minuit.GetParameter(0,a,ea);
minuit.GetParameter(1,b,eb);
##Stampa dei parametri
print("a = %f +- %f, b = %f +- %f"%(a.value,ea.value,b.value,eb.value))

##*****************************************************************************************************************************************##
##PROGRAMMA 2 (versione 1): COMODO                                                                                                         ##
##MINIMIZZAZIONE DELLA FUNZIONE chi2 (fornendole parametri) DI CHI2 A PARTIRE DA UNA FUNZIONE F LINEARE NEI PARAMETRI CON PACCHETTO iminuit##
##*****************************************************************************************************************************************##
from   iminuit import Minuit 
import numpy as np

##Funzione di fit lineare nei parametri: funzione TF1 da fittare come al primo anno 
def f(x,a,b):
    return a*x+b

##Funzione da minimizzare con esplicitazione dei parametri
def chi2(a,b):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],a,b))/ey[i])**2 
    return val

##----##
##Main##
##----##
x  = np.array([]); y  = np.array([]); ex = np.array([]); ey = np.array([])
for line in open("pendolo.dat"):
    dt  = line.split()  ##divisione della riga in una lista
    if len(dt)!=4:      ##se la lista non e' divisa in 4 (dati), il dato non e' accettato
        continue
    ##Si converte da stringa a float e si riempono i vettori di numpy
    x   = np.append(x,  float(dt[0])); y   = np.append(y,  float(dt[1])) 
    ex  = np.append(ex, float(dt[2])); ey  = np.append(ey, float(dt[3]))


##Interfaccia iminuit

m = Minuit(chi2, a=4, b=0, print_level = 0)
#m.print_level = 2  ##setta parametri verbosita' stampa
m.migrad()

print(m.values) ##nomi default in cui salva valori ed errori
print(m.errors)

##***************************************************************************************************************************************##
##PROGRAMMA 2 (versione 2): COMODO                                                                                                       ##
##MINIMIZZAZIONE DELLA FUNZIONE FCN (fornendole array) DI CHI2 A PARTIRE DA UNA FUNZIONE FUNC LINEARE NEI PARAMETRI CON PACCHETTO iminuit##
##***************************************************************************************************************************************##
from   iminuit import Minuit 
import numpy as np

def f(x,a,b):
    return a*x+b

def chi2(par): ##stesso del par.py, MA diamo par array di numpy
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],par[0],par[1]))/ey[i])**2
    return val

x  = np.array([]); y  = np.array([]); ex = np.array([]); ey = np.array([])
for line in open("pendolo.dat"):
    dt  = line.split() 
    if len(dt)!=4:
        continue
    x   = np.append(x,  float(dt[0])); y   = np.append(y,  float(dt[1]))
    ex  = np.append(ex, float(dt[2])); ey  = np.append(ey, float(dt[3]))


par = np.array([4.0,0.0])
#m = Minuit(chi2, par) Python3
m= Minuit.from_array_func(chi2,par) ##Python 2 
m.migrad()

print(m.values)
print(m.errors)

##**********##
##HANDS ON 3##
##**********##

##*******************************************************************************************************************************##
##PROGRAMMA 3:                                                                                                                   ##
##MINIMIZZAZIONE DELLA FUNZIONE FLOGL (-LOG(LIKELIHOOD)) PER GENERICA PDF; FIT BINNED DI LIKELIHOOD CON PACCHETTO iminuit E MULTI##
##*******************************************************************************************************************************##
from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

##Si definisce -log(Likelihood) BINNATA 
def flogl(tau):
    val = 0
    for i in range(1, h.GetNbinsX()+1):
        ni = h.GetBinContent(i) ##si acquisiscono eventi nel singolo bin
        xmin = h.GetBinLowEdge(i)
        xmax = h.GetBinLowEdge(i)+h.GetBinWidth(i)
        ## pi e' l'INTEGRALE della pdf (1/tau e^-t/tau) tra gli estremi dei bin
        pi = exp(-xmin/tau) - exp(-xmax/tau)
        ##Calcolo effettivo della Likelihood Binnata
        val = val - ni*log(pi)
    return val

##MAIN##

##Istogramma
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))
    
##Python3
m = Minuit(flogl,tau=2) ##minimizzazione con istanziazione di minuit e funzione flogl e parametro tau
m.errordef = 0.5
m.print_level = 2 


'''
##Python2
m = Minuit(flogl,tau=2,errordef=0.5,print_level=3)
m.migrad()       
'''
##Si ricava valore dei parametri e si disegna l'istogramma
tau = m.values[0]
h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(1,tau)
f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))

##Fit con Multi per Likelihood Binnata
f.FixParameter(0,1)
h.Fit('f', '0MULTI') ##lo zero non disegna quella spiacciacata perche' normalizzata
f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
f.Draw("SAME")


gApplication.Run(True)

##************************************************************************************************************************************##
##PROGRAMMA 4:                                                                                                                        ##
##MINIMIZZAZIONE DELLA FUNZIONE FLOGL (-LOG(LIKELIHOOD)) PER GENERICA PDF; FIT BINNED DI EXTENDED LIKELIHOOD CON PACCHETTO iminuit E L##
##************************************************************************************************************************************##
from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

##Si definisce -log(Likelihood) BINNATA con parametro norm parametro che rappresenta il numero di eventi (si fitta anche il numero di eventi)
def flogl(tau,norm):
    val = 0
    for i in range(1,h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        xmin = h.GetBinLowEdge(i)
        xmax = h.GetBinLowEdge(i)+h.GetBinWidth(1)
        ## pi e' l'INTEGRALE della pdf (1/tau e^-t/tau) tra gli estremi dei bin
        pi = exp(-xmin/tau)-exp(-xmax/tau)
        mui = norm*pi
        val = val - (ni*log(mui)-mui)
    return val

##----##
##Main##
##----##

##Lettura file di dati ed istogramma
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

##Si istanzia un oggetto di iminuit
m = Minuit(flogl, tau=2, norm=1000, errordef = 0.5, print_level = 3)##non si fitta solo tau, ma anche il numero di eventi

##Comando di minimizzazione che esegue automaticamente MIGRAD
m.migrad()

##Acquisizione valori dei parametri
tau = m.values[0]
etau = m.errors[0]
norm = m.values[1]
enorm = m.errors[1]

# tau = m.values[0]
h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(1,tau)
f.SetParameter(0,norm*h.GetBinWidth(1))
f.Draw('SAME')

h.Fit('f','L')

gApplication.Run(True)
