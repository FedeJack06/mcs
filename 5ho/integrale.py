import ROOT
import math

rnd = ROOT.TRandom3()
rnd.SetSeed(158375846)

R = 1
Rcl = R/2
Ntot=4000000 #errore come rad(conteggio) aumento fattore 4, errore si dimezza
Nacc = 0
Nacc_sph = 0
for i in range(Ntot):
    x = (2*rnd.Rndm()-1)*R #cerco punti casuali fuori dalla sfera
    y = (2*rnd.Rndm()-1)*R #punti casuali generati fra 1 e 2
    z = (2*rnd.Rndm()-1)*R
    r = math.sqrt(x*x+y*y+z*z)
    rcl = math.sqrt(x*x+y*y)
    if r<R and rcl>R/2:
        Nacc += 1
    if r<R:
        Nacc_sph += 1

p = Nacc/Ntot
ep = math.sqrt(p*(1-p)/Ntot)

ps = Nacc_sph/Ntot
eps = math.sqrt(ps*(1-ps)/Ntot)

vol = (2*R)**3

print("vol solido: %6.3f +- %6.3f"%(p*vol, ep*vol))
print("vol sfera ideale: %6.3f",4/3.*math.pi*R**3)
print("vol sfera monte carlo: %6.3f +- %6.3f"%(ps*vol, eps*vol))
