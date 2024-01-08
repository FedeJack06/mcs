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
    ix2 = h2D_H0.GetYaxis().FindBin(TestData[i,1]) # x2

    fH0= hx1_H0.GetBinContent(ix1)+offset
    fH1= hx1_H1.GetBinContent(ix1)+offset
    ratio1D = fH1/(fH0+fH1)

    fH0= h2D_H0.GetBinContent(ix1, ix2)+offset
    fH1= h2D_H1.GetBinContent(ix1, ix2)+offset
    ratio2D = fH1/(fH0+fH1)

    vscore1D = np.append(vscore1D, ratio1D)
    vscore2D = np.append(vscore2D, ratio2D)

plt.hist(vscore2D[TestLab==0], bins=100, range=(0,1))
plt.hist(vscore2D[TestLab==1], bins=100, range=(0,1))
plt.show()

model=MLPClassifier()
#model = LinearDiscriminantAnalysis()
model.fit(TrainData, TrainLab)
vscoreLD=model.predict_proba(TestData)[:1]

fp2D, tp2D, th = metrics.roc_curve(TestLab, vscore2D)
plt.plot(tp2D, (1-fp2D))


fp1D, tp1D, th = metrics.roc_curve(TestLab, vscore2D)
plt.plot(tp1D, (1-fp1D))

fpLD, tpLD, th = metrics.roc_curve(TestLab, vscoreLD)
plt.plot(tpLD, (1-fpLD))


plt.show()

auc1D =metrics.auc(fp1D, tp1D)
auc2D =metrics.auc(fp2D, tp2D)
aucLD=metrics.auc(fpLD, tpLD)

print ("AUC 1D ", auc1D)
print ("AUC 2D ", auc2D)
print ("AUC LD ", aucLD)

#Fisher
#MLP
# model = MLPClassifier()

