#metodo dei trapezi (n=numero intervallini fissato)
def integN(f, a, b, n):
    w   = (b-a)/n
    val = (f(a)+f(b))*w/2 #eq che evita ricalcolo estremi
    for i in range (1, n-1):
        x = a+w*i
        val += w*f(x)
    return val


#cambio numero intervalli finche sono sotto precisione voluta
#eps = precisione 
def integPrec(f, a, b, eps):
    n=2
    val1 = integN(f,a,b,n)
    while True:
        val0 = val1
        val1 = integN(f,a,b,n*2)
        n = n*2
        if abs(val0 - val1) < eps:
            break
    return val1


def fun(x):
  return  x**3

print(integPrec(fun,0,1,0.00001))
