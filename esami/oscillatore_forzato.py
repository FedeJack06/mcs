import math as m
import numpy as np
import matplotlib.pyplot as plt

mass=1
k=0.25
A=0.1
w=0.25

def acc(x, t): #per oscillatore forzato
    return A/mass*m.sin(w*t)-k/mass*x

dt = 0.01
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

##  verlet velocity ##
for i in range(0, n):
    t[i+1] = t[i] + dt
    x[i+1] = x[i] + dt*v[i] + dt**2*0.5*acc(x[i], t[i])
    v[i+1] = v[i] + dt/2*(acc(x[i+1], t[i+1]) +acc(x[i], t[i]))

##  grafico ##
plt.plot(t, x)
plt.xlabel("Tempo [s]")
plt.ylabel("Posizione [m]")
plt.title("oscillatore forzato")
plt.show()
            
