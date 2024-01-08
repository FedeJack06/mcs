#!/usr/bin/env python
# coding: utf-8

# # calcolo volumi 3D
# 

# da una sfera di raggio R estraiamo il volume di un cilindo di raggio r tutto contenuto all interno

# con il metodo di reiezione genero punti dentro alla sfera e tolgo quelli che sono dentro al cilindo. il numero di punti che sono accetti/ numero di punti generati è proporzionale al volume.
# La sfera è un po complicata quindi generiamo dentro un cubetto cosi da poter generare uniformente in x,y,z anziche r^2, sin(theta) , d(phi)

from ROOT import *
import math as m

R = 1
rc = R/2
n = 1000000


rnd = TRandom3()
rnd.SetSeed(123456789)

n1 = 0.0
for i in range(0,n):
    
    x = 2*R*rnd.Rndm() - R
    y = 2*R*rnd.Rndm() - R
    z = 2*R*rnd.Rndm() - R
    
    
    #volume della sfera
    '''
    if(x**2+y**2+z**2 < R**2):
        n1 += 1
    '''
    if((x**2+y**2+z**2 < R**2) and (x**2+y**2 > rc**2)):
        n1 += 1
    
(n1/n)*((2*R)**3)



