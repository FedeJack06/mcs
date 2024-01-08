##***************************##
##import di Python piu' usati##
##***************************##
import math as m
import numpy as np
import matplotlib.pyplot as plt
from ROOT import *

##******************************##
##Lettura da file e da terminale##
##******************************##

##-------------------------------------------##
##Costanti richieste all'utente via terminale##
print("Fornire il dato DATO: ")
DATO = float(input())
##-------------------------------------------##

##------------------------------------------------------------##
##Lettura del file di dati e salvataggio degli stessi in array##
##------------------------------------------------------------##
x  = np.array([]); y  = np.array([]); ex = np.array([]); ey = np.array([])
for line in open("pendolo.dat"):
    dt  = line.split() ##divisione della riga in una lista
    if len(dt)!=4:     ##se la lista non e' divisa in 4 (dati), il dato non e' accettato
        continue
    ##Si converte da stringa a float e si riempono i vettori di numpy
    x   = np.append(x,  float(dt[0])); y   = np.append(y,  float(dt[1]))
    ex  = np.append(ex, float(dt[2])); ey  = np.append(ey, float(dt[3]))

##-----------------------------------------------------##
##Istogramma e riempimento da file con un dato per riga##
##-----------------------------------------------------##
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

##------------------------------------------------##
##Lettura ed utilizzo solo di una colonna del file##
##------------------------------------------------##
x1 = np.array([])
for line in file1:
    val = line.split()
    x1 = np.append(x1,float(val[0]))
    h1.Fill(float(val[0]))

##*********************************##
##Grafici ed abbellimenti in Python##
##*********************************##
import matplotlib.pyplot as plt

plt.plot(t,x)
plt.xlabel('Tempo (s)')
plt.ylabel('Posizione (m)')
plt.title('Andamento di x in funzione di t')
plt.show()

##**********************##
##Comandi per istogrammi##
##**********************##
from ROOT import *

h = TH1D("h","Titolo",50,0.,0.)
h.Draw()
h.Fit("funzione fit")

h.GetMean() ##per media
h.GetRMS()  ##per deviazione standard
h.GetEntries()
h.GetBinWidth(1)

gApplication.Run(True)

##***************##
##Comandi per FIT##
##***************##

##Si definisce funzione di Fit da utilizzare con i vari parametri su Istogramma o altro:
##Gaussiana di TMath
f = TF1("f","[0]*TMath::Gaus(x,[1],[2],1)",0.,0.)
##[1] media
##[2] deviazione standard, sigma
