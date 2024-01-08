from ROOT import *
import math as m
import numpy as np

N=100000
R=5
r=1
rho=0.08
rnd=TRandom3()
rnd.SetSeed(123456789)

nacc=0
for i in range(0,N):
    #genero un dominio alto 2, largo e profondo 12 centrato in 0
   x=2*(R+r)*rnd.Rndm()-(R+r)
   y=2*(R+r)*rnd.Rndm()-(R+r)
   z=2*r*rnd.Rndm()-r
   s=z**2-(m.sqrt(x**2+y**2)-R)**2

   if s<=r**2:
       nacc=nacc+1

prob=nacc/N
vol= prob*(((2*(R+r))**2)*(2*r)) #probabilita per volume totale del dominio di generazione
vol_teorico= m.pi*(r**2)*2*m.pi*R

I= (0.25)*vol*rho*(3*(r**2) + 4*(R**2))

I_teo= (0.25)*vol_teorico*rho*(3*(r**2) + 4*(R**2))

print("volume ",vol,"momento inerzia ",I,"momento inerzia teorico ",I_teo)
