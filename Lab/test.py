#!/usr/bin/python
    
import sys,serial
from dmm import *
from ps  import *

#Pilotaggio power supply
#Inizializzazione
instr = psinit("USB0::0x0AAD::0x0135::035442613::INSTR")

#Selezione canale 1
pssel(instr,1)


#File di output
file = open('uv.dat','w')
#Configurazione seriale
ser = serial.Serial('COM3', 9600)

#Lettura dal multimetro
t0=time.time()
v_gen = 1.0
v_out = 0
while v_out < 6:
    valV = v_gen
    cmd  = f'APPLY {valV},0.1'
    instr.write(cmd)
    if time.time()-t0 > 1.5:
        t0 = time.time()
        
        V,eV = dmmread(ser)
        print(V,eV)
        v_out = V
        file.write(str(V)+" ")
        file.write(str(eV)+" ")
        file.write(str(v_gen)+" ")
        file.write(str(0)+" ")
        file.write('\n')
        v_gen += 0.1
    
