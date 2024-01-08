##**********##
##STIMA M_PI##
##**********##
from ROOT import *

##Generazione casuale di numeri
rnd = TRandom3()
rnd.SetSeed(3141592653)

##Meta' del lato del quadrato e raggio del cerchio inscritto
l = 1

##Estrazione
n = 100000
n_in_crf = 0
n_in_Q = 0

for i in range(0,n):
    x = 2*l*rnd.Rndm() - l
    y = 2*l*rnd.Rndm() - l
    n_in_Q = n_in_Q + 1
    if x*x+y*y<l*l:
        n_in_crf = n_in_crf + 1

M_PI = n_in_crf/n_in_Q*4

print("M_PI = %f"%M_PI)

##***********************************##
##SVILUPPO IN ESERCIZIO IPER-SFERA 4D##
##***********************************##
from ROOT import *
import math as m

##Estrazione
rnd = TRandom3()
rnd.SetSeed(123456789)

##Meta' del lato dell'iper-cubo e raggio dell'iper-sfera
r = 1

##Volume teorico
dim   = 4 ##dimensione della iper-sfera
V_teo = m.pi**(dim/2)/m.gamma(dim/2+1)*r**dim

##Estrazione
N = 10000
n_in_S = 0
n_in_C = 0

for i in range(0,N):
    x = 2*r*rnd.Rndm() - r
    y = 2*r*rnd.Rndm() - r
    z = 2*r*rnd.Rndm() - r
    t = 2*r*rnd.Rndm() - r
    n_in_C = n_in_C + 1
    if x*x+y*y+z*z+t*t<r*r:
        n_in_S = n_in_S + 1

alpha = n_in_S/n_in_C*16

print("alpha = %f"%alpha)
print("Volume teorico = %f"%V_teo)
VMC = alpha*r**dim
print("Volume MC = %f"%VMC)



    
