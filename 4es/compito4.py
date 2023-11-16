'''
 Sviluppo del metodo di Numerov 
'''
import matplotlib.pyplot as plt
import numpy as np
import math

'''
  S1: definire il potenziale in funzione della variabile normalizzata xi
'''
def V(xi):
    return xi**2               #potenziale armonico
    #return xi**2 + 0.075*xi**4 #potenziale anarmonico
    #return xi**4 - 2*xi**2 + 1 #doppia buca in 1 e -1, bariera centrale alta 1
    #return xi**4 - 4*xi**2 + 4 #doppia buca in rad 2 e -rad 2, bariera centrale alta 4
    '''if abs(xi)<1:               #buca di potenziale rettangolare
        return 0
    else:
        return 10'''
    
'''
  S1: calcolo di b a partire dall'energia normalizzata eps, della coordinata
  normalizzata xi e dallo passo h (variabile globale)
'''
#h passo tra i punti equazione da trovare, dichiarata nel "main"
def b(eps,xi):
    k = 2*eps - V(xi) #per potenziale armonico
    #k = eps - V(xi)    #per altri potenziali
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

def numerov(n1,n2,eps):  #indice primo, ultimo step ed energia
    psi = np.array(xi)*0 # copio xi in psi e lo azzero
    j   = np.sign(n2-n1) #+1 n2>n1 sx-->dx
                         #-1 n2<n1 dx-->sx
    psi[n1] = 0.0
    psi[n1+j] = 1e-4     #così picco di ordine 10^8, se metto =10 oridine picco 10^13
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
    psil = numerov(0,nmatch+1,eps)       #0 ad nmatch +1, 1 punto in piu serve perche derivate centrali
    psir = numerov(n-1,nmatch-1,eps)     #paro dal fondo fino ad 1 punto oltre nmatch
    rapporto = psil[nmatch]/psir[nmatch]
    psir = psir*rapporto                 #raccordo psi l e r
    Dpsil = (psil[nmatch+1] - psil[nmatch-1])/(h*2)
    Dpsir = (psir[nmatch+1] - psir[nmatch-1])/(h*2)
    return Dpsil-Dpsir                   #differenza derivate prime r e l

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
  Raccordare psil e psir --> psi
'''

e = findE(1, 2, 0.00001)  #tra che estremi imporre energia e precisione
print("Energia dello stato graficato: ", e)

psi = np.concatenate((psil[:nmatch], psir[nmatch:]), axis=0) #uso psi left per parte left e psi r per parte r
#plt.plot(xi,psi)
#plt.show()

############################SPETTRO DELL'ENERGIA
#quando oltrepasso un'energia accettabile cambia segno la diff tra le derivate

#findAllE(energia massima da trovare, step tra gli intervalli di energia, precisione valori energie)
def findAllE(energiamax,step,tol):
    energie = np.array([])  #array contenente le energie esatte trovate
    a = 0                   #estremo inferiore dell'intervallo in cui controllo il cambio segno della derivata
    b = a + step            #estremo superiore dell'intervallo di controllo
    while b < energiamax:
        if evalDerivative(b)*evalDerivative(a) < 0:             #se segno differenza derivate è cambiato
            energie = np.append(energie, findE(a, b, tol))      #valuto energia esatta
        a = b                                                   #estremo inferiore = inf precedente
        b = a + step                                            
    if evalDerivative(energiamax)*evalDerivative(a) < 0:        #controllo l'ultimo intervallo 
        energie = np.append(energie, findE(a, energiamax, tol))
    return energie

print("Calcolo spettro dell'energia...")
print("Energie: ", findAllE(3, 0.1, 1e-5));                  #spettro dell'energia

#############################NORMALIZZAZIONE
#funzione d'onda come array y = psi, x = xi, dimensione n
#integro con i trapezi
def integDiscreto(f, x): #integDiscreto(numpy array y, np array x)
    if f.size == x.size:
        w   = abs(x[1]-x[0])               #intervallo x
        n   = x.size                       #numero di punti
        val = 0                            #area
        for i in range (0, n-1):
            val = val + (f[i]+f[i+1])*w/2
        return val
    else:
        return 999

NormaPsi = integDiscreto(abs(psi)**2, xi)
print("Norma di psi: ", NormaPsi)
psiNormalizzato = ( 1/(NormaPsi**(1/2)) )*psi
print("Norma di psi normalizzato: ", integDiscreto(abs(psiNormalizzato)**2, xi))

fig, (axes0, axes1) = plt.subplots(2)
axes0.plot(xi, psiNormalizzato)
axes0.set_title("Funzione d'onda normalizzata")

#############################DENSITÀ PROBABILITÀ

densProb = abs(psiNormalizzato)**2
axes1.plot(xi, densProb)
axes1.set_title("Densità di probabilità")
plt.show()
