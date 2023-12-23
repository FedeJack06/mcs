from ROOT import *
import numpy as np

from sklearn import metrics
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.neural_network import MLPClassifier

import matplotlib.pyplot as plt

#Access ROOT histograms
file_train = TFile("mva_train.root")
hx1_H0 = file_train.Get("hx1_H0")
hx1_H1 = file_train.Get("hx1_H1")
h2D_H0 = file_train.Get("h2D_H0")
h2D_H1 = file_train.Get("h2D_H1")
hx1_H0.Scale(1/hx1_H0.Integral())
hx1_H1.Scale(1/hx1_H1.Integral())
h2D_H0.Scale(1/h2D_H0.Integral())
h2D_H1.Scale(1/h2D_H1.Integral())

Train      = np.loadtxt("mva_train.txt")
Test       = np.loadtxt("mva_test.txt")

##############
# x1 x2 lab

TrainData   = Train[:,0:2]
TestData    = Test[:,0:2]
TrainLab    = Train[:,2]
TestLab     = Test[:,2]

vscore1D = np.array([])
vscore2D = np.array([])
offset   = 1e-9

#Likelihood ratio (1D/2D)
for i in range(0,len(TestLab)):
    ix1 = h2D_H0.GetXaxis().FindBin(TestData[i,0]) # x1
    ix2 = h2D_H0.GetXaxis().FindBin(TestData[i,1]) # x2

    fH0 = hx1_H0.GetBinContent(ix1)+offset #se offset piccolo eliman solo gli zeri
    fH1 = hx1_H1.GetBinContent(ix1)+offset
    ratio1D = fH1/(fH0+fH1) #per motivi estetici oppure fh1/fh0
    
    fH0 = h2D_H0.GetBinContent(ix1, ix2)+offset #se offset piccolo eliman solo gli zeri
    fH1 = h2D_H1.GetBinContent(ix1, ix2)+offset
    ratio2D = fH1/(fH0+fH1)

    vscore1D = np.append(vscore1D, ratio1D)
    vscore2d = np.append(vscore2D, ratio2D)

plt.hist(vscore2D[TestLab==0], bins=100, range=(0,1))
#se avessi def la funz L-P varia da +- inf, invece cosi ogni punto, se normalizzato, ratio va da 0 a 1
#trasformo in vero falso lindice
plt.hist(vscore2D[TestLab==1], bins=100, range=(0,1))
plt.show()

#falsi positivi 1d, true positive
fp1D, tp1D, th = metrics.roc_curve(TestLab, vscore1D)
plt.plot(tp1D, (1-fp1D))
fp2D, tp2D, th = metrics.roc_curve(TestLab, vscore2D)
plt.plot(tp2D, (1-fp2D))
plt.show()

auc1d = metrice.auc(fp1D, tp1D)

#Fisher
# model = LinearDiscriminantAnalysis()

#MLP
# model = MLPClassifier()

