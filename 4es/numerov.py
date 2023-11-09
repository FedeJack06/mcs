'''
 Sviluppo del metodo di Numerov 
'''
import matplotlib.pyplot as plt
import numpy as np
import math

'''
  S1: definire il potenziale in funzione della variabile normalizzata xi
'''
#gamma = 0.075
def V(xi):
    #return xi**2 + gamma*xi**4
    return xi**2
'''
  S1: calcolo di b a partire dall'energia normalizzata eps, della coordinata
  normalizzata xi e dallo passo h (variabile globale)
'''
#h passo tra i punti equazione da trovare, dichiarata nel "main"
def b(eps,xi):
    k = 2*eps - V(xi)
    return k*h**2/12

'''
  S1/S2: completare la funzione Numerov che riempe i valori di psi(xi) 
         dall'indice n1 all'indice n2 (entrambi compresi)
         Schema:
           - definisco indice j in modo che 1 se n2>n1, -1 se n2<n1
             in questo modo:
               se j =  1 indice i, i+j,i+2*j -> i, i+1, i+2
               se j = -1 indice i, i+j,i+2*j -> i, i-1, i-2
           - fornisco i primi due valori di psi
           - implemento Numerov (ciclo for)
'''

def numerov(n1,n2,eps): #indice primo, ultimo step ed energia
    psi = np.array(xi)*0  # copio xi in psi e lo azzero
    j   = np.sign(n2-n1) #+1 n2>n1 sx-->dx
                         #-1 n2<n1 dx-->sx
    psi[n1] = 0.0
    psi[n1+j] = 1e-4 #così picco di ordine 10^8, se metto =10 oridine picco 10^13
                     #non conta quanto piccolo sia, viene riscalato il resto in proporzione

    for i in range(n1 + 2*j, n2 + j, j): #0, n-1, 0.5
        psi[i] = (2*psi[i-j]*(1-5*b(eps, xi[i-j])) - psi[i-2*j]*(1+b(eps, xi[i-2*j])) )/(1+b(eps, xi[i]))
    return psi

'''
  S3: completare evalDerivative
     - per l'energia eps fornita dall'utente crea soluzione left e right
     - le normalizza a nmatch (si consiglia di normalizzare psir a psil)
     - calcola la differenza (diff) tra le derivate centrate (left e right) in match
'''
def evalDerivative(eps):
    global psir,psil
    psil = numerov(0,nmatch+1,eps) #0 ad nmatch +1, 1 punto in piu serve perche derivate centrali
    psir = numerov(n-1,nmatch-1,eps) #paro dal fondo fino ad 1 punto oltre nmatch
    rapporto = psil[nmatch]/psir[nmatch]
    psir = psir*rapporto #raccordo psi l e r
    Dpsil = (psil[nmatch+1] - psil[nmatch-1])/(h*2)
    Dpsir = (psir[nmatch+1] - psir[nmatch-1])/(h*2)
    return Dpsil-Dpsir #differenza derivate prime r e l

''' 
  Metodo di bisezione per trovare l'energia in cui la funzione evalDerivative
  e' nulla. Cioe' l'enegia per cui  la derivata sinistra e destra coincidono 
'''
def findE(emin,emax,tol):
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;

''' 
  Codice principale: l'esecuzione dello script parte da qui
'''
n       = 14000
nmatch  = 10000 #dove xi=rad(2*eps) ossia V(x)=E, pasta cercare dove funzione psi non piccola
xi      = np.linspace(-7.,7,n)
h       = xi[1]-xi[0]

'''
  S1: verifico Numerov chiamando la funzione da sinistra a destra
  e la disegno
'''
epsilon = 0.5   # o altra energia di stato definito eps = (n+1/2)
psi=numerov(0,n-1,epsilon)
plt.plot(xi,psi,'.r')
plt.show()

'''
  S2: come S1 ma verifico che funzioni anche da destra a sinistra
  e la disegno
'''
epsilon = 0.5   # o altra energia di stato definito eps = (n+1/2)
psi=numerov(n-1,0,epsilon)
plt.plot(xi,psi,'.b')
plt.show()

'''
  S3:
   - commentare i punti precedenti (a parte le definizioni iniziali del Main code
   - completare evalDerivative 
   - chiamare findE 
   - fare grafico delle due funzioni 
'''
#e = findE(3, 5, 0.00001)  #tra che estremi imporre energia e precisione
#print("Energy ", e)

'''
  S4:
   - copiare psr nella parte 'vuota' di psil di modo che psil rappresenti tutta psi(x)
     nell'intervallo dato o, alternativamente, copiarle entrambe in una nuova psi
   - disegnare la funzione d'onda trovata
'''
#psi = np.concatenate((psil[:nmatch], psir[nmatch:]), axis=0) #uso psi left per parte left e psi r per parte r
#plt.plot(xi,psi)
#plt.show()
