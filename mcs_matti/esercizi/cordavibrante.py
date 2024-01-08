import numpy as np
import matplotlib.pyplot as plt
import math

#impongo i parametri fisici della corda vibrante
#lunghezza della corda, numero di divisioni e vettore x,tempo
L=0.5
N=100
x=np.linspace(0,L,N)
t=0.01
tend=100
#dt,dx e velocita
dt=0.001
dx=L/N
v=0.01
vprimo=dx/dt

psi1=np.zeros(N) #vettore al tempo presente
psi2=np.zeros(N) #vettore al tempo futuro
psi0=np.zeros(N) #vettore al tempo passato

#condizione iniziale
A=2
k=5*np.pi/L #deve essere un certo numero di pi greco/L
psi0=A*np.sin(x*k)

#primo passo
psi1[1:-1] = psi0[1:-1]+(v**2/vprimo**2)*(psi0[2:]+psi0[0:-2]-2*psi0[1:-1])

#faccio scorrere un istante di tempo
t=t+dt
j=0

plt.figure()

while t<tend:
    #itero gli altri passi
    psi2[1:-1] = 2*psi1[1:-1] - psi0[1:-1] + (v/vprimo)**2 * (psi1[2:]+psi1[1:-1]-2*psi1[0:-2])
    #faccio scorrere il tempo
    t=t+dt
    #plotto
    if j % 10:
        plt.clf()
        plt.plot(x,psi1)
        plt.draw()
        plt.pause(1e-08)

    psi0[:] = psi1[:]
    psi1[:] = psi2[:]
    j=j+1
