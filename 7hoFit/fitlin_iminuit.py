from iminuit import Minuit
from numpy   import *
import matplotlib.pyplot as plt

def f(x,par):
    return par[1]*x+par[0]

def chi2(par):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],par))/ey[i])**2
    return val

# Acquisizione dati
x,y,ex,ey = loadtxt('pendolo.dat',usecols=(0,1,2,3),unpack=True)

## Chiamo Minuit nella modalita' parametri passati tramite array

