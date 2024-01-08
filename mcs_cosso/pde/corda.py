import numpy as np
import matplotlib.pyplot as plt


def gaussian(x, mu, sig):
    return np.exp(-np.power(x - mu, 2.) / (2 * np.power(sig, 2.)))

L = 20.
v = 1

npo = 100
x = np.linspace(0,L,npo)
#y = np.sin(3*np.pi*(x/L)) #condizione iniziale: Sinusoidale
y = gaussian(x,L/2,1) #condizione iniziale: Gaussiana centrata in L/2

plt.plot(x,y,'r.')
plt.draw()
plt.pause(1e-5)

dx = x[3]-x[2]
vp = v+0.01 #condizione di stabilità
dt = dx/vp


y2 = np.copy(y)
ynew = np.zeros(len(y))
ynew[1:npo-1] = y[1:npo-1] + 0.5*((v**2)/(vp**2))*(y[2:npo]+y[0:npo-2]-2*y[1:npo-1]) #primo passo
plt.clf()
plt.plot(x,ynew,"r.")
plt.draw()
y = np.copy(ynew)


t=dt
tend=20
while(t < tend):
    
    ynew[1:npo-1] = 2*y[1:npo-1] - y2[1:npo-1] + ((v**2)/(vp**2))*(y[2:npo]+y[0:npo-2]-2*y[1:npo-1])
    plt.clf()
    plt.plot(x,ynew,"r.")
    plt.ylim(-1,1)
    plt.draw()
    plt.pause(1e-5)
    
    y2 = np.copy(y)
    y = np.copy(ynew)
    t += dt

plt.show()

