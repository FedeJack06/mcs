#sbarra di calore (metodo esplicito)

from ROOT import*
import numpy as np
import math as m
import matplotlib.pyplot as plt

L=0.5
k=2
N=100
eta=3/5

t=0
tend=1000
dx=L/N
dt=eta*dx*dx*k

x=np.linspace(1,L,N);
T=np.zeros(N)
Tsucc=np.zeros(N)
z=np.zeros(N)

#condizione iniziale
l= 2*dx
T[49]=1/l
T[50]=1/l
T[51]=1/l


i=0
while t<tend:
    for i in range(1,N-2):
        Tsucc[i]=T[i]+eta*(T[i+1]+T[i-1]-2*T[i])

    plt.clf()
    
    plt.plot(x,T)
    plt.draw()
    plt.pause(1e05)
    
    T=Tsucc
    t=t+dt
    i=i+1


