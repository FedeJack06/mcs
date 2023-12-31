from iminuit import Minuit
from numpy   import *
import matplotlib.pyplot as plt

def f(x,par):
    return par[1]*x+par[0]

def chi2(par):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],par))/ey[i])**2/(ey[i]**2 + (par[1]*ex[i])**2)
    return val

# Acquisizione dati
x,y,ex,ey = loadtxt('pendolo.dat',usecols=(0,1,2,3),unpack=True)

## Chiamo Minuit nella modalita' parametri passati tramite array
par = array([0, 4])
mn = Minuit(chi2,par)
mn.print_level = 4 #livello che mi da minuit sull'informazione
mn.migrad()
print("beta_0: %f +- %f "%(mn.values[0],mn.errors[0]))
print("beta_1: %f +- %f "%(mn.values[1],mn.errors[1]))
mn.draw_mnmatrix(cl=[1,2,3])
plt.show()
