import math as m
import numpy as np
import matplotlib.pyplot as plt


##QUESTA PARTE DI ESERCIZIO DELLA SIMULAZIONE.
rho0 = 8000
rho  = 1
mu   = 0.001
r    = 0.01
g    = 9.81


def Cd(v):
    vmod=abs(v)
    Re=2*rho*r/mu
    return 24*vmod/Re+4*vmod**(3/2.)/m.sqrt(Re)*0.4*vmod**2

def acc(x,v,t):
    mass=4/3.*m.pi*r**3*rho0
    F=-0.5*Cd(v)*rho*r**2*v/abs(v)-mass*g
    return F/mass

def acc_a(x,v,t):
    
    mass=4/3.*m.pi*r**3*rho0
    m0=4/3.*m.pi*r**3*rho
    F=-0.5*Cd(v)*rho*r**2*v/abs(v)-mass*g
    F=acc(x,v)*mass+m0*g
    return F/mass

n=1000
t=np.zeros(n) #la struttura deve essere questa, cioe array di lunghezza determinata cosi che i for possano fare le loro cose
x=np.zeros(n)
v=np.zeros(n)


#condizioni iniziali
t[0]=0
x[0]=100
v[0]=0.00001
dt=0.01



#RK2
'''
for i in range(0,n-1):
    
    k1=dt*v[i]
    w1=dt*acc(x[i],v[i],t[i])
    k2=dt*(v[i]+w1/2)
    w2=dt*acc(x[i]+k1/2,v[i]+w1/2,t[i]+0.5*dt)
    
    x[i+1]=x[i]+k2
    v[i+1]=v[i]+w2
    t[i+1]=t[i]+dt

'''



#Verlet Velocity
'''
for i in range(0,n-1):

    x[i+1]=x[i]+dt*v[i]+0.5*dt**2*acc(x[i],v[i],t[i])
    v[i+1]=v[i]+0.5*dt*(acc(x[i],v[i],t[i])+acc(x[i+1],v[i+1],t[i]+dt))
    t[i+1]=t[i]+dt

'''



#Eulero Cromer
'''
for i in range(0,n-1):
    
    v[i+1]=v[i]+dt*acc(x[i],v[i],t[i])
    x[i+1]=x[i]+dt*v[i+1] 
    t[i+1]=t[i]+dt
'''



#Verlet Position
'''

x[1]=2*x[0]+dt**2*acc(x[0],v[0],t[0])
t[1]=dt
for i in range(1,n-1):
    
    x[i+1]=2*x[i]-x[i-1]+dt**2*acc(x[i],v[i],t[i])
    t[i+1]=t[i]+dt

'''


plt.plot(t,x)
plt.show()
