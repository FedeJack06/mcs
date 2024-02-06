import matplotlib.pyplot as plt
import numpy as np
import string #for print letter loop

data = np.loadtxt(fname="input", dtype="float")#, delimiter=",")
freq = data[:, 0:6:2] #inzio(compreso) : fine(compresa) : passo(inizio+=passo)
err = data[:, 1:6:2]
ia = 0 #indice di colonna dei subplots

fig, ax = plt.subplots(3,3,layout='constrained', sharey=True)
fig.suptitle("")
for i in [15,20,25]:
    x = np.array(['SF',100,200,300,400])#se tipi differenti, dati equispaziati sulle x

    y = err[i:i+5, 0] #prima riga di subplots
    ax[0,ia].plot(x,y)
    ax[0,ia].set_ylabel("y []")
    ax[0,ia].set_xlabel("("+string.ascii_lowercase[ia]+")          x []")

    y2 = err[i:i+5, 1] #seconda riga di subplots
    ax[1,ia].plot(x,y2)
    ax[1,ia].set_ylabel("y2 []")
    ax[1,ia].set_xlabel("("+string.ascii_lowercase[ia+3]+")          x2 []")

    y3 = err[i:i+5, 2] #terza riga di subplots
    ax[2,ia].plot(x,y3)
    ax[2,ia].set_ylabel("y3 []")
    ax[2,ia].set_xlabel("("+string.ascii_lowercase[ia+6]+")          x3 []")
    ia = ia+1 #colonna successiva
    
''' MODIFICA ASSI SOLO DI CERTI SUBPLOTS
ax[2,0].set_xlabel("(g)          B [MHz]")
ax[2,1].set_xlabel("(h)          B [MHz]")
ax[2,2].set_xlabel("(i)          B [MHz]")

ax[0,0].set_ylabel("Err_Chi_Tot")
ax[1,0].set_ylabel("Err_Chi_Tot")
ax[2,0].set_ylabel("Err_Chi_Tot")'''

ax[0,0].set_title("")
ax[0,1].set_title("")
ax[0,2].set_title("")

fig.set_figheight(15)#inches
fig.set_figwidth(15)
plt.show()
