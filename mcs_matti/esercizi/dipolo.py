import numpy as np
import matplotlib.pyplot as plt

#vettore potenziale
L=0.5
N=101
vold=np.zeros([N,N])
vnew=np.zeros([N,N])

x=np.linspace(0,L,N)
y=np.linspace(0,L,N)

X,Y=np.meshgrid(x,y)

#cariche
eps0=8.85e-12
rho=np.zeros([N,N])
rho[50,(50-10)]=0.01
rho[50,(50+10)]=-0.01

#tempo
t=0
tend=1
dt=1e-03

#uso Gauss-Seidel
while t<tend:

    for j in range(1,N-1):
        for i in range(1,N-1):
            vold[i,j]=np.copy((1./4.)*(vold[i+1,j]+vold[i-1,j]+vold[i,j+1]+vold[i,j-1])+(1./(4*eps0))*rho[i,j]*(L/N)**2)

    t=t+dt
    
    
fig,ax=plt.subplots(subplot_kw={"projection":"3d"})
ax.plot_surface(X,Y,vold)    
plt.show()
