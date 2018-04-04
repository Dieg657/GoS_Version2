import math

def ErlangB(E,M):
    InversoProbBloqueio = 1.0
    for i in range(1, M):
        InversoProbBloqueio = 1.0 + ((i / E) * InversoProbBloqueio)
    Bloqueio = 1.0 / InversoProbBloqueio
    return Bloqueio * 100

def ErlangC(E,M,P):
    ePower = E**M
    mFactorial = math.factorial(M)
    X = ePower / mFactorial * (M/(M-E))
    Y = 0
    for i in range(0, M):
        a = E**i
        b = math.factorial(i)
        Y = Y + (a/b)
    return (X / ((X+Y))) * 100

def ocupacaoVia(E, M):
    return (E/M) * 100

def faixasRequeridas(M,Fator):
    return (M/(1 - (Fator/100)))

def nivelServico(B, M , E, ANT, MediaDuracao):
    C = -((M-E) * ANT/MediaDuracao)
    C = math.pow(math.e, C)
    Resultado = 1 - (B * C)
    return Resultado * 100



print("{:.2f}".format(ErlangC(10, 11,1)) + "%")
print("{:.2f}".format(ErlangB(83,80)) + "%")
print("{:.2f}".format(ocupacaoVia(10, 14)) + "%")
print("{:.2f}".format(nivelServico(0.239,11,10,20,180)) + "%")
print("Faixas de rolamento: {}".format(faixasRequeridas(186, 5)))
