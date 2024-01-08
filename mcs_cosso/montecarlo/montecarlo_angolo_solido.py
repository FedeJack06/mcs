#!/usr/bin/env python
# coding: utf-8

# # simulazione esperimento a sogente radioattiva 

from ROOT import *
import math as m


# simulazione del processo di decadimento di una sorgente radioattiva.

# bisogna iniziare a generare i fotoni in maniera uniforme sull'angolo solido d(omega) = sin(theta) d(theta) d(phi) = -d(cos(theta)) d(phi)


n = 1000000
d = 0.2
l = 0.01


rnd = TRandom3()
rnd.SetSeed(123456789)


# calcolo la direzione del mio fotone: in coord polari


n1 = 0.0
n3 = 0.0
for i in range(0,n):
    phi = 2*m.pi*rnd.Rndm()
    costhe = 2*rnd.Rndm()-1 #estraggo il cos fra -1 e 1
    the = m.acos(costhe)
    alpha = d/costhe
    x = alpha*m.cos(phi)*m.cos(the)
    y = alpha*m.cos(phi)*m.sin(the)
    
    if(the > m.pi/2):
        continue
    if((abs(x) < l/2) and (abs(y) < l/2)):
        n1 += 1
        
    if(x>0 and x<l and y>0 and y<l): #sposto il quadrato non piu centrato
        n3 += 1

#calcolo montecarlo
print(n3)
# calcolo approssimato

n2 = (l**2)/(4*m.pi*d**2)


