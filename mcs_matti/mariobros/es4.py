from ROOT import*

x=0

file = open("DatiGamma.dat","r")

h= TH1D("h","titolo",40,0.,0.)

for x in file:
    h.Fill(float(x))

h.Draw()

#t=TTree()
#t.ReadFile("DatiGamma.dat","t/D")


f=TF1("f","[0]*((x**2*exp(-x/[1]))/2*[1]**3)",0.,0.)

f.SetParameter(0,1)
f.SetParameter(1,5.74/3)

#t.UnbinnedFit("f","t")

h.Fit("f","L")

print("theta ",f.GetParameter(1),"p-value ",f.GetProb())

    
gApplication.Run(True)
