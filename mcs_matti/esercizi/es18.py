from ROOT import *

ntot=1000000
rnd=TRandom3()
rnd.SetSeed(123456789)

t=TTree()
h=TH1D("h","",50,0.,0.)
f=TF1("f","[0]*[1]*pow(x,[1]-1)",0,1)
f.SetParameter(1,3)
f.FixParameter(0,1)

file=open("daties18.dat","x")

for i in range(0,ntot):
    #faccio l'istogramma solo per disegnare, in realta il fit con TTree
    x=rnd.Rndm()**(1/3)
    h.Fill(x)
    file.write(repr(x))
    file.write('\n')


t.ReadFile("daties18.dat","t/D")
t.UnbinnedFit("f","t")

h.Draw()
f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))

f.Draw("SAME")

gApplication.Run(True)
