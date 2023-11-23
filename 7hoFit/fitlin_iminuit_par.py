from   iminuit import Minuit
from   numpy   import *
import matplotlib.pyplot as plt

def f(x,m,q):
    return m*x+q

def chi2(a,b): #m,q
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],a,b))/ey[i])**2
    return val

# Acquisizione dati
x,y,ex,ey = loadtxt('pendolo.dat',usecols=(0,1,2,3),unpack=True)
mn = Minuit(chi2, a=4, b=0)
mn.print_level = 3 #livello che mi da minuit sull'informazione
mn.migrad()
print("beta_0: %f +- %f "%(mn.values[0],mn.errors[0]))
print("beta_1: %f +- %f "%(mn.values[1],mn.errors[1]))
mn.draw_mnmatrix(cl=[1,2,3])
plt.show()

## Chiamo Minuit nella modalita' parametri passati tramite passaggio dei singoli parametri
## Esplorare la funzione draw_mnmatrix per fare i contour

