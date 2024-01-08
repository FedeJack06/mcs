from ROOT import *

nobs=30
nb=15
prob=0

for i in range(0,nobs):
    prob += TMath.PoissonI(i,nb)

if 1-prob<0.05:
    print("rigettata")
else:
    print("non rigettata")

print(1-prob)

ns=0
while(True):
    prob=0
    for i in range(0,nobs):
        prob +=TMath.PoissonI(i,nb+ns)
    if prob<0.025:
        print("Upper limit al 95% CL",ns-1)
        break
    ns =ns +1

ns=0
while(True):
    prob=0
    for i in range(0,nobs):
        prob +=TMath.PoissonI(i,nb+ns)
    if 1-prob>0.025:
        print("Lower limit 95% CL",ns-1)
        break
    ns=ns+1
