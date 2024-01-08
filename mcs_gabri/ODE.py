##------------------------------------------------##
##STRUTTURA GENERICA PER LA RISOLUZIONE DI UNA ODE##
##------------------------------------------------##

##---------------------------------------------##
##Si importano le librerie di Python necessarie##
##---------------------------------------------##
import math as m
import numpy as np
import matplotlib.pyplot as plt

##----------------------------------------------------------##
##Si definiscono funzioni utili per il seguito del programma##
##con uso di costanti dichiarate successivamente nel MAIN.  ##
##----------------------------------------------------------##

##Esempio di accelerazione definita a partire da forza di attrito viscoso e forza peso##
def acc(x,v):
    mass = 4/3.*m.pi*r**3*rho0
    if abs(v)!=0:
        F = -0.5*CD(v)*rho*r**2*v/abs(v)-mass*g ##CD(v) funzione specifica del problema
    else:
        F = -mass*g
    return F/mass

'''
Se si ha equazione differenziale (es.: oscillatore armonico), si definisce la funzione a partire dalla stessa equazione formalmente come a = f(v,x,t); a e' spesso indicata nell'equazione come derivata seconda di x.
'''
def acc(x, t):
    return A/mass*m.sin(w*t)-k/mass*x

##----##
##MAIN##
##----##

##----------------------##
##Costanti, in unita' SI##
##----------------------##

#mass = 1
#w    = 0.25
#...

##-----------------------##
##Dati per la risoluzione##
##-----------------------##

##1)Viene fornito un tempo di simulazione iniziale ed uno finale##
dt  = 0.05           ##passo temporale
tin = 0              ##tempo iniziale
tf  = 100            ##tempo finale

n = int((tf-tin)/dt) ##numero di passi

##Array con elementi indicizzati da 0 a n necessari per immagazzinare i dati della risoluzione##
t = np.zeros(n+1) ##evoluzione temporale
x = np.zeros(n+1) ##evoluzione spaziale
v = np.zeros(n+1) ##evoluzione velocita'

##Condizioni iniziali##
t[0] = 0
x[0] = 1
v[0] = 0

##2)Si lascia simulare a discrezione##

n  = 1000 ##si setta il numero di passi risolutivi
dt = 0.05 ##passo temporale

##Array con elementi indicizzati da 0 a n necessari per immagazzinare i dati della risoluzione##
t = np.zeros(n+1) ##evoluzione temporale
y = np.zeros(n+1) ##evoluzione spaziale
v = np.zeros(n+1) ##evoluzione velocita'

##Condizioni iniziali##
t[0] = 0
v[0] = 0
y[0] = 10000

##***********************************************##
##METODI RISOLUTIVI PER L'EQUAZIONE DIFFERENZIALE##
##***********************************************##

##Metodo di Eulero##
for i in range(0,n):
    k1 = dt*v[i]
    w1 = dt*acc(y[i],v[i])

    y[i+1] = y[i] + k1
    v[i+1] = v[i] + w1
    t[i+1] = t[i] + dt

##Runge - Kutta al secondo ordine##
for i in range(0,n):
    k1 = dt*v[i]
    w1 = dt*acc(y[i],v[i])

    k2 = dt*(v[i]+w1*0.5)
    w2 = dt*acc(y[i]+k1*0.5, v[i]+w1*0.5)

    y[i+1] = y[i] + k2
    v[i+1] = v[i] + w2
    t[i+1] = t[i] + dt

##Runge - Kutta al quarto ordine##
for i in range(0,n):
    k1 = dt*v[i]
    w1 = dt*acc(y[i],v[i])

    k2 = dt*(v[i]+w1*0.5)
    w2 = dt*acc(y[i]+k1*0.5, v[i]+w1*0.5)

    k3 = dt*(v[i]+w2*0.5)
    w3 = dt*acc(y[i]+k2*0.5, v[i]+w2*0.5)

    k4 = dt*(v[i]+w3)
    w4 = dt*acc(y[i]+k3, v[i]+w3)

    y[i+1] = y[i] + k1*(1./6.) + k2*(1./3.) + k3*(1./3.) + k4*(1./6.)
    v[i+1] = v[i] + w1*(1./6.) + w2*(1./3.) + w3*(1./3.) + w4*(1./6.)
    t[i+1] = t[i] + dt

##Verlet position##
'''
Servono due condizioni iniziali sulla posizione, per cui si traduce l'informazione iniziale sulla velocita' in una informazione sulla posizione con un passo di RK2.
'''
k1 = dt*v[0]
w1 = dt*acc(y[0],v[0])

k2 = dt*(v[0]+w1*0.5)
w2 = dt*acc(y[0]+k1*0.5, v[0]+w1*0.5)

y[1] = y[0] + k2
v[1] = v[0] + w2
t[1] = t[0] + dt

'''
A questo punto, si implementa l'algoritmo per verlet position.
'''
for i in range(1,n):
    x[i+1] = 2*x[i] - x[i-1] + dt**2*acc(t[i])
    t[i+1] = t[i] + dt

##Verlet velocity##
for i in range (0, n):
    t[i+1] = t[i] + dt
    x[i+1] = x[i] + dt*v[i] + dt**2*0.5*acc(x[i],t[i])
    v[i+1] = v[i] + dt*0.5*(acc(x[i+1], t[i+1])+acc(x[i], t[i]))

##Eulero - Cromer (conservazione del momento angolare L)##
for i in range(0,n-1):
    x[i+1] = x[i] + v[i]*dt
    v[i+1] = v[i] + acc(x[i+1])*dt
    t[i+1] = t[i] + dt

##Verlet Position alternativo (preferibilemnte da non usare)##
x = np.zeros(n + 1)
v = np.zeros(n + 1)
t = np.zeros(n + 1)
x[0] = x0
v[0] = v0
t[0] = t0
for i in range(1, n + 1):
        t[i] = t[i - 1] + dt
        x[i] = x[i - 1] + v[i - 1] * dt + 0.5 * acc(x[i - 1], t[i - 1]) * dt**2
        v[i] = v[i - 1] + 0.5 * (acc(x[i - 1], t[i - 1]) + acc(x[i], t[i])) * dt


##-------##
##Grafico##
##-------##
plt.plot(t,x)
plt.xlabel('Tempo (s)')
plt.ylabel('Posizione (m)')
plt.title('Andamento di x in funzione di t')
plt.show()

##Check##
#print(t[n])  ##tempo finale e verifica: si ottiene effettivamente il t[n] voluto, ovvero tf?



