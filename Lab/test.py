#!/usr/bin/python
    
import sys,serial
from dmm import *
from ps  import *

#Pilotaggio power supply
#Inizializzazione
print(rm.list_resources()) #onetime
usb_address = input()
instr = psinit(usb_address)
#instr = psinit("USB0::0x0AAD::0x0135::035375056::INSTR")

#Selezione canale 1
pssel(instr,1)
#Erogazione di 12 V
valV = 12
cmd  = f'APPLY {valV},0.1'
instr.write(cmd)

#File di output
file = open('outLed.dat','w')
#Configurazione seriale
ser = serial.Serial('COM2', 9600)

#Lettura dal multimetro
t0 = 0
count = 0
if time.time() - t0 > 5 and count < 3:
    t0 = time.time()

    command(ser,'VDC')
    V,eV = dmmread(ser)
    print(V,eV)
    file.write(str(V)+'\t')
    file.write(str(eV)+'\t')

    command(ser,'ADC')
    I,eI = dmmread(ser)
    print(I,eI)
    file.wrtie(str(I)+'\t')
    file.wrtie(str(eI)+'\t')
    file.write('\n')
    count+=1
