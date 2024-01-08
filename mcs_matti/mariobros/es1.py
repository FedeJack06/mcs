#esercizio 1: sfera 4d con montecarlo

from ROOT import *
import math as m
import numpy as np

N=10000000
R=5
n=4
rnd=TRandom3()
rnd.SetSeed(123456789)

nacc=0
for i in range(0,N):
   x=2*R*rnd.Rndm()-R
   y=2*R*rnd.Rndm()-R
   z=2*R*rnd.Rndm()-R
   t=2*R*rnd.Rndm()-R
   r=x**2+y**2+z**2+t**2

   if m.sqrt(r)<=R:
       nacc=nacc+1

prob=nacc/N
vol=prob*((2*R)**n) #probabilità per volume totale del dominio di generazione

alpha=vol/(R**n)

alpha_teorico=(m.pi**(n/2))/(TMath.Gamma(n/2+1))

print("volume ",vol,"alpha ",alpha,"alpha teorico ",alpha_teorico)
