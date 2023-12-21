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
    ix2 = h2D_H0.GetXaxis().FindBin(TestData[i,1]) # x2


#Fisher
# model = LinearDiscriminantAnalysis()

#MLP
# model = MLPClassifier()

