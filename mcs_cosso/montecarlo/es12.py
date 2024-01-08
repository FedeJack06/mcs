from ROOT import *
import numpy as np
from scipy import stats

app = TApplication("app",0,0)

mu = 50

rnd = TRandom3()
rnd.SetSeed(123456789)
h = TH1D("h","",53,0.,0.)
x = np.array([])

s = 0
i = 0
q = 0
n = 4000
for i in range(n):
    while(s < mu):
        
        k = rnd.Rndm()
        dt = -np.log(1-k)
        s += dt
        q += 1
        #print(q,s)

    s = 0
    #print("____________________________________________")
    h.Fill(q-1)
    x = np.append(x,q-1)
    q = 0

c = TCanvas()
f = TF1("f","[1]*TMath::Poisson(x,[0])")
c.Draw()
#f.SetParameters(mu,4030)

############ binned extended: ritorna un p-value di 0.6 
f.FixParameter(0,mu)
f.SetParameter(1,4030)
h.Fit("f","LL")


#h.Draw("same")
p1 = f.GetProb()
print(p1)
#f.Draw("SAME")


############ ooooooooooooooooooooooooooooo
#poisson discreta quindi cosi non si puo fare

'''
po = stats.poisson(mu)
#D1, p = stats.kstest(x, po.cdf)
D1, p = stats.kstest(x, "poisson", args=(5,))
print(p)
'''

##possiamo fare un test di chi2 o likelihood (chi2 male prche code non bene)



app.Run(True)
