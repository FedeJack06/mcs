import math as m
import numpy as np
import matplotlib.pyplot as plt

#######################################
##### ES forza attrito e forza peso
rho0 = 8000
rho  = 1
mu   = 0.001
r    = 0.01
g    = 9.81

def Cd(v):
    vmod=abs(v)
    Re=2*rho*r/mu
    return 24*vmod/Re+4*vmod**(3/2.)/m.sqrt(Re)*0.4*vmod**2

def acc(x,v,t): #accelerazione da froza di attrito viscoso e forza peso
    mass=4/3.*m.pi*r**3*rho0
    F=-0.5*Cd(v)*rho*r**2*v/abs(v)-mass*g
    return F/mass

def acc_a(x,v,t):
    mass=4/3.*m.pi*r**3*rho0
    m0=4/3.*m.pi*r**3*rho
    F=-0.5*Cd(v)*rho*r**2*v/abs(v)-mass*g
    F=acc(x,v)*mass+m0*g
    return F/mass
###########################################
################# ES oscillatore forzato
mass=1
k=0.25
A=0.1
w=0.25

def acc(x, t): #per oscillatore forzato
    return A/mass*m.sin(w*t)-k/mass*x


###########################################
################ inizializzazioni
dt = 0.01 #delta t fra i passi
tin = 0 #tempo iniziale
tf = 100 #tempo finale

n = int((tf-tin)/dt)#numero di passi

t = np.zeros(n+1)#evoluzione temporale
x = np.zeros(n+1)#evoluzione spaziale
v = np.zeros(n+1)#evoluzione velocità
#condizioni iniziali
t[0]=0
x[0]=1
v[0]=0

###############################################
################# METODI RISOLUTIVI
#Runge-Kutta 2 ordine
'''
for i in range(0,n):
    k1=dt*v[i]
    w1=dt*acc(x[i], v[i], t[i])

    k2=dt*(v[i]+w*0.5)
    w2=dt*acc(x[i]+k*0.5, v[i]+w*0.5, t[i]+dt*0.5)
    
    x[i+1]=x[i] + k2
    v[i+1]=v[i] + w2
    t[i+1]=t[i] + dt
'''
'''
for i in range(0,n):
    k1 = dt*v[i]
    w1 = dt*acc(y[i],v[i])

    k2 = dt*(v[i]+w1*0.5)
    w2 = dt*acc(y[i]+k1*0.5, v[i]+w1*0.5)

    y[i+1] = y[i] + k2
    v[i+1] = v[i] + w2
    t[i+1] = t[i] + dt
'''
#Runge-Kutta al 4 ordine
'''
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
'''

#Eulero Cromer (momento angolare viene conservato)
'''
for i in range(0,n):
    v[i+1] = v[i] + dt*acc(x[i],v[i],t[i])
    x[i+1] = x[i] + dt*v[i+1] 
    t[i+1] = t[i] + dt
'''
#Verlet Velocity
'''
for i in range (0, n):
    t[i+1] = t[i] + dt
    x[i+1] = x[i] + dt*v[i] + dt**2*0.5*acc(x[i],t[i])
    v[i+1] = v[i] + dt*0.5*(acc(x[i+1], t[i+1])+acc(x[i], t[i]))
'''
#Verlet Position (deriva da principio di minima azione)
'''#metodo1 punti iniziali con Eulero
x[1] = 2*x[0] + dt**2*acc(x[0],v[0],t[0])
t[1] = t[0] + dt
for i in range(1,n):
    x[i+1] = 2*x[i] -x[i-1] + dt**2*acc(x[i],v[i],t[i])
    t[i+1] = t[i] + dt
'''
#Metodo 2: servono due condizioni iniziali sulla posizione, per cui si traduce l'informazione iniziale sulla velocita' in una informazione sulla posizione con un passo di RK2.
'''
k1 = dt*v[0]
w1 = dt*acc(y[0],v[0])

k2 = dt*(v[0]+w1*0.5)
w2 = dt*acc(y[0]+k1*0.5, v[0]+w1*0.5)

y[1] = y[0] + k2
v[1] = v[0] + w2
t[1] = t[0] + dt
#A questo punto, si implementa l'algoritmo per verlet position.
for i in range(1,n):
    x[i+1] = 2*x[i] - x[i-1] + dt**2*acc(t[i])
    t[i+1] = t[i] + dt
'''
##Verlet Position alternativo (preferibilemnte da non usare)##
'''
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
'''

plt.plot(t,x)
plt.show()
