import numpy as np

def integDiscreto(f, x): #(numpy array y, np array x)
    if f.size == x.size:
        w   = abs(x[1]-x[0])
        n   = x.size
        val = 0
        for i in range (0, n-1):
            val = val + (f[i]+f[i+1])*w/2
        return val
    else:
        return 999

f = [1, 2, 3]
x = [1, 2, 3]

print(integDiscreto(np.array(f), np.array(x)))
