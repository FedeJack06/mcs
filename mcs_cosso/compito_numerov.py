'''
 Il warning ottenuto una volta lanciato il programma cenrcando su internet deve essere
 dovuto ad un bug di matplotlib non so bene che fare
'''

import matplotlib.pyplot as plt
import numpy as np
import math


def V(xi):
    return xi**2
    #return xi**2+y*xi**4
    

def b(eps,xi):
    return (h**2/12)*(2*eps-V(xi))


def numerov(n1,n2,eps):
  psi = np.array(xi)*0  # copio xi in psi e lo azzero
  B = b(eps,xi)         
  j = np.sign(n2-n1)
  psi[n1] = 0
  psi[n1+j] = 1e-6
  for i in range(n1+2*j,n2+j,j):
    psi[i] = (2*psi[i-j]*(1-5*B[i-j])-psi[i-2*j]*(1+B[i-2*j]))/(1+B[i])
  return psi


def evalDerivative(eps):
    global psir,psil
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    alpha = psil[nmatch]/psir[nmatch]
    psir = alpha*psir
    #psil[nmatch]=psir[nmatch]
    d_psil = (psil[nmatch+1]-psil[nmatch-1])/(2*h)
    d_psir = (psir[nmatch+1]-psir[nmatch-1])/(2*h)
    return d_psil-d_psir


def findE(emin,emax,tol):
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;


def numerov_corr(eps):                                   #compito
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    alpha = psil[nmatch]/psir[nmatch]
    psir = alpha*psir
    psi_tot = psil
    psi_tot[nmatch:n] = psir[nmatch:n]
    return psi_tot



## funzione che fa alcune delle cose chieste per compito
def plot(eps):                                          #compito
    
    #calcolo funzione d onda e plot della densita di probabilita
    psi_tot = numerov_corr(eps)
    
    fig, axs = plt.subplots(2)
    #normalizzaizone della funzione d onda
    k = np.trapz(psi_tot**2,xi)
    fig.subplots_adjust(0.09,0.067,0.955,0.932,0.4,0.26)
    
    #plot funzione normalizzata
    axs[0].set_title('Funzione d\'onda normalizzata ad energia {} '.format(str(eps)[0:7]))
    axs[0].plot(xi,psi_tot/np.sqrt(k))

    #plot della densita di probabilita
    axs[1].set_title('Densità di probabilità ad energia {} '.format(str(eps)[0:8]))
    axs[1].plot(xi,(psi_tot/np.sqrt(k))**2)


    #calcolo del numero di zeri
    f = 0
    for i in range(0,psi_tot.size-1):
        if(psi_tot[i]*psi_tot[i+1] < 0):
            f += 1
    print("--------------------------------------")
    print("Numero di zeri: ",f)


    
    
'''
   *************************************************************
   Codice principale: l'esecuzione dello script parte da qui   *
   *************************************************************
'''       


n       = 14000
nmatch  = 10000
xi      = np.linspace(-7.,7.,n)
#y       = 0.05
h       = xi[1]-xi[0]

#setto l'energia massima 
E_max   = 8  #per correttezza dico che  non capisco per quale ragione ma mettendo E_max = 9 trova un altro livello di energia (ovviamente sbagliato) a 8.74... 
E = np.arange(0,E_max,0.1)

#interval è un array di zeri, qunado l intervallo di energia contiene uno zero
#della diff di derivate ci metto un 1 cosi da sapere in quali intervalli abbiamo uno zero

interval = np.zeros(E.size)
energie = []
for i in range(0,E.size-1):
    if(evalDerivative(E[i])*evalDerivative(E[i+1]) < 0):
        e = findE(E[i],E[i+1],0.0001)
        print("**************************************")
        print("Energia: ", e)
        interval[i] = 1
        energie.append(e)
        plot(e)
            
print(interval)
plt.show()




