from ROOT import *
import numpy as np
import time
import sys
from tqdm import tqdm

rnd    = TRandom3()
rnd.SetSeed(int(time.time()))

hx1_1 = TH1D("hx1_H0","",50,0,3)
hx1_2 = TH1D("hx1_H1","",50,0,3)
hx2_1 = TH1D("hx2_H0","",50,0,5)
hx2_2 = TH1D("hx2_H1","",50,0,5)
hx2D_1 = TH2D("h2D_H0","",50,0,3,50,0,5)
hx2D_2 = TH2D("h2D_H1","",50,0,3,50,0,5)

n        = 100000
filename = "mva"
if len(sys.argv)<=1:
    print("Please input nevents filename (if the filename contains train or test it will perform training or test sample generation")
    exit(1)
if len(sys.argv)>=3:
    n = int(sys.argv[1])
    filename = sys.argv[2]

csi    = 1
lam    = 1
sig0   = 0.5
muH0   = 1.3
muH1   = 1.7

vx1 = np.array([])
vx2 = np.array([])
vlab = np.array([])
for i in tqdm(range(n)):
    if rnd.Rndm()<0.5:
        mu  = muH0
        lab = 0
    else:
        mu  = muH1
        lab = 1
    x2  = -lam*log(rnd.Rndm())
    sig = sig0*exp(-x2/csi)
    x1  = rnd.Gaus(mu,sig)
    
    vx1  = np.append(vx1,x1)
    vx2  = np.append(vx2,x2)
    vlab = np.append(vlab,lab)

    if lab==0:
        hx1_1.Fill(x1)
        hx2_1.Fill(x2)
        hx2D_1.Fill(x1,x2)
    else:
        hx1_2.Fill(x1)
        hx2_2.Fill(x2)
        hx2D_2.Fill(x1,x2)

if "test" in filename:
    filetxt = filename+".txt"
    np.savetxt(filetxt,np.c_[vx1,vx2,vlab])
        
if "train" in filename:
    filetxt = filename+".txt"
    np.savetxt(filetxt,np.c_[vx1,vx2,vlab])
        
    hx1_1.Smooth(1,"k5b")
    hx1_2.Smooth(1,"k5b")
    hx2_1.Smooth()
    hx2_2.Smooth()
    hx2D_1.Smooth(1,"k5b")
    hx2D_2.Smooth(1,"k5b")

    c = TCanvas()
    c.Divide(3,1)
    c.cd(1)
    hx1_1.Draw()
    hx1_2.Draw("SAME")
    hx1_2.SetLineColor(2)
    c.cd(2)
    hx2_1.Draw()
    hx2_2.Draw("SAME")
    hx2_2.SetLineColor(2)
    c.cd(3)
    hx2D_1.Draw()
    hx2D_2.Draw("SAME")
    hx2D_2.SetMarkerColor(2)
    hx2D_1.SetMarkerStyle(20)
    hx2D_2.SetMarkerStyle(20)
    
    filename = filename+".root"
    file = TFile(filename,"recreate")
    hx1_1.Write()
    hx1_2.Write()
    hx2_1.Write()
    hx2_2.Write()
    hx2D_1.Write()
    hx2D_2.Write()
    file.Close()

    gApplication.Run(True)
