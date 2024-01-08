##***************************##
##NUMEROV E RELATIVI SVILUPPI##
##***************************##
'''
 Schema per lo sviluppo del metodo di Numerov con potenziale armonico 
'''
import matplotlib.pyplot as plt
import numpy as np
import math

'''
  Definizione del potenziale armonico in funzione della variabile normalizzata xi
'''   
def V(xi):
    return xi**2
    
'''
  Si calcola b, come definito a lezione, a partire dall'energia normalizzata eps, dalla coordinata
  normalizzata xi e dal passo h (variabile globale)
'''
def b(eps,xi):
    k = 2*eps-V(xi)
    b = (h**2/12)*k 
    return b

'''
 Definizione della funzione del metodo di Numerov
'''
def numerov(n1,n2,eps):
    psi = np.array(xi)*0  # copio xi in psi e lo azzero
    j   = np.sign(n2-n1)
    psi[n1] = 0
    psi[n1+j] = 1e-8
    for i in range(n1+2*j,n2+j,j):
        b_n = b(eps,xi[i-j])
        b_nmen = b(eps,xi[i-2*j])
        b_npi = b(eps,xi[i])
        psi[i] = (2*psi[i-j]*(1-5*b_n)-psi[i-2*j]*(1+b_nmen))/(1+b_npi)
    return psi

'''
 Definizione della funzione che confronta le derivate di psil e psir
'''
def evalDerivative(eps):
    global psir,psil
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    psir = (psil[nmatch]/psir[nmatch])*psir
    dpsildpsi = (psil[nmatch+1]-psil[nmatch-1])*1/(2*h)
    dpsirdpsi = (psir[nmatch+1]-psir[nmatch-1])*1/(2*h)
    diff = dpsildpsi-dpsirdpsi
    return diff

''' 
  Metodo di bisezione per trovare l'energia in cui la funzione evalDerivative
  e' nulla, ovvero l'enegia per cui  la derivata sinistra e destra coincidono. 
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
Funzione per il calcolo numerico dell'integrale del modulo quadro di psil
'''
def integ_trap(fun):

    ##Valutazione contributo ad estremi di fun:
    ##si osserva che il contributo deve essere zero visto che in numerov primo ed ultimo estremo di psi sono fissati a zero;
    ##tuttavia, per completezza dell'algoritmo si inserisce l'implementazione
    val = (fun[0]+fun[n-1])*h/2
    
    ##Valutazione dei contributi per xi,fun \in (-7,7)
    for i in range(1,fun.size):
        val += h*fun[i]

    return val


''' 
 Codice principale
'''
n       = 14000
nmatch  = 10000
xi      = np.linspace(-7.,7.,n)
h       = xi[1]-xi[0] 


'''
Definizione dell'intervallo di energia da considerarsi [0,E_max] con zero 0 chiamato inizio_eps 
'''
inizio_eps = 0
E_max = 5
passo = 0.1


'''
Divisione di [0,E_max] nei sottointervalli in cui si vogliono trovare i livelli energetici
'''
divisioni = int(E_max/passo)
intervalli = np.linspace(inizio_eps,E_max,divisioni)
livello = 0

'''
Ricerca dei livelli energetici nei singoli sottointervalli e salvataggio degli stessi in una list
'''
energie = []
for i in range(0,intervalli.size-1):
    if evalDerivative(intervalli[i])*evalDerivative(intervalli[i+1])<=0:
        e = findE(intervalli[i],intervalli[i+1],0.0001)
        print("L'energia per il livello energetico con n == %d e': %f" %(livello,e))
        energie.append(e)
        livello += 1


    

'''
Calcolo della funzione d'onda per un valore a scelta di quelli trovati
'''
epsilon = energie[1] 
evalDerivative(epsilon)

'''
Grafico della funzione d'onda, unendo parte sinistra e destra
'''
for i in range(nmatch+2,n):
     psil[i] = psir[i]

plt.plot(xi,psil)
plt.title("Grafico della funzione d'onda non normalizzata")
plt.xlabel('xi')
plt.ylabel('psi')
plt.show()

'''
Normalizzazione della funzione d'onda
'''

## Modulo quadro

modulo_quadro = psil*psil

## Calcolo dell'integrale del modulo quadro di psil con xi \in [-7,7]

I = integ_trap(modulo_quadro)

normalizzazione = math.sqrt(I)

## Calcolo della funzione normalizzata e relativo grafico

psil_nor = psil/normalizzazione

plt.title("Grafico della funzione d'onda normalizzata")
plt.plot(xi,psil_nor)
plt.xlabel('xi')
plt.ylabel('psi')
plt.show()

## Verifica dell'avvenuta normalizzazione della funzione

A = (integ_trap(psil_nor**2))

print("Come atteso, l'integrale del modulo quadro di psil_nor è: ", A)

##*************************************##
##VERLET POSITION, AMBEDUE LE DIREZIONI##
##*************************************##
import matplotlib.pyplot as plt
import numpy as np
import math

def a(sigma,f,x):
    return -f/(sigma**2)+x*x/(sigma**4)*f;

def soleq(n1,n2,sigma):
    #creo f (copia d x)
    f = np.array(x)
    j = np.sign(n2-n1)
    f[n1] = 0
    f[n1+j] = 1e-6
    for i in range(n1+2*j,n2+j,j):
        #f(n+1) = 2*f(n) - f(n-1) + h*h*a(n)
        f[i]   = 2*f[i-j] - f[i-2*j] + h*h*a(sigma,f[i-j],x[i-j])
    return f

# main code
n      = 10000
x      = np.linspace(-5.,5,n)
h      = x[1]-x[0]
f      = soleq(9999,0,1)
sigma = 1

plt.plot(x,f,'r.')
plt.show()
