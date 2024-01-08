##**********##
##HANDS ON 4##
##**********##

from   sys   import *
from   math  import *
from   ROOT  import *
import numpy as np
from   scipy import stats

##Carica due file che danno distribuzioni a prima vista esponenziali
file1 = open("s1.dat")
file2 = open("s2.dat")

h1 = TH1D("h1","",12,0,0.5) ##più fine più chi2 simile ks fino a che troppo pochi valori
h2 = TH1D("h2","",12,0,0.5)

##Lettura da files
x1 = np.array([])
for line in file1:
    val = line.split()
    x1 = np.append(x1,float(val[0]))
    h1.Fill(float(val[0]))

x2 = np.array([])
for line in file2:
    val = line.split()
    x2 = np.append(x2,float(val[0]))
    h2.Fill(float(val[0]))

h1.SetLineColor(kRed)    
h1.Draw("E")

h2.Draw("ESAME")
gApplication.Run(True)

##*****************************************************##
##DOMANDE SULLA COMPATIBILITA' TRA LE DUE DISTRIBUZIONI##
##*****************************************************##

##----------------------------------------##
##1)Le due distribuzioni sono compatibili?##
##----------------------------------------##
##TEST DEL CHI2 BINNED
##Metodo di TH1D che eredita da TH1 e lo trovo lì: metodo su istogramma e si passa come argomento il secondo istogramma
##OSS.: sarebbe necessario un puntatore, ma in Python l'interfaccia e' banalizzata
print("Test chi2")
if h1.Chi2Test(h2) > 0.05:
    print("Test superato; compatibili")
    print("Probabilita' chi2: ", h1.Chi2Test(h2))
else:
    print("Test NON superato; NON compatibili")
    print("Probabilita' chi2: ", h1.Chi2Test(h2))
    
print("Verifica scambiando istogrammi su cui agisce il metodo:")
print(h2.Chi2Test(h1)) ##si verifica che cambiando stesso conteggio (1 su 2 e 2 su 1 stessa cosa)

##TEST DI KOLMOGOROV-SMIRGOV UNBINNED SU 2 CAMPIONI DI DATI
t_ks, p_ks = stats.ks_2samp(x1,x2) ##si passano i due array di dati per estrarre la test statistic e p value
print("Test ks")
##print(t_ks)
if p_ks > 0.05:
    print("Non rigettabile ipotesi di compatibilita' dei campioni")
    print("p-value: ",p_ks)
else:
    print("Rigettare ipotesi compatibilita' dei campioni")
    print("p-value: ",p_ks)

##------------------------------------------------------------------------##
##2)Un campione di dati e' compatibile con una distribuzione teorica nota?##
##------------------------------------------------------------------------##

##TEST DI KOLMOGOROV-SMIRGOV UNBINNED SU 1 CAMPIONI DI DATI ED UNA pdf NOTA
test = stats.expon(loc=0,scale=0.1)##funzione specifica per esponenziale da cercare sotto stats.kstest
t_ks1, p_ks1 = stats.kstest(x1,test.cdf)
print("Test ks con parametro noto 0.1")
##print(t_ks1)
if p_ks1 > 0.05:
    print("Non rigettabile ipotesi di compatibilita' dei campioni")
    print("p-value: ",p_ks1)
else:
    print("Rigettare ipotesi compatibilita' dei campioni")
    print("p-value: ",p_ks1)

##Analogo per eventuale altra distribuzione
t_ks2, p_ks2 = stats.kstest(x2,test.cdf)
print("Test ks con 0.1")
print(p_ks2)
print(t_ks2)

##--------------------------------------------------------------------------##
##2)Un campione di dati e' compatibile con una distribuzione teorica ignota?##
##--------------------------------------------------------------------------##
##TEST CON FIT SU UNA pdf CON PARAMETRI IGNOTI
f = TF1("exp","[0]/[1]*exp(-x/[1])",0,0.5);
f.SetParameter(0,1)##non so nulla ma lo do perchè default denominatore è 0
f.SetParameter(1,1)##non so nulla ma lo do perchè default denominatore è 0
h1.Fit("exp")

if f.GetProb() > 0.05:
    print("Test superato; compatibili")
    print("Probabilita' chi2: ", f.GetProb())
else:
    print("Test NON superato; NON compatibili")
    print("Probabilita' chi2: ", f.GetProb())

##Analogo per eventuale altra distribuzione
h2.Fit("exp")
print(f.GetProb())
