#ifndef PYCALCULOS_H
#define PYCALCULOS_H
#include "header.hpp"

class PyC{
private:
    PyObject *moduleMainString;
    PyObject *moduleMain;
    PyObject *func;
    PyObject *args;
    PyObject *result;
public:
    PyC();
    void desalocarPy();
    double calcularBloqueio(double erlang, long slot);
    double calcularProbEspera(double erlang, long slot);
    double calcularOcupacaoVia(double erlang, long slot);
    double faixasRequeridas(long faixas, long fator);
    double nivelServico(double eC, double erlang, long slot, long tempoDesejado, long tempoSimulado);
    ~PyC();
};

#endif // PYCALCULOS_H

PyC::PyC()
{
    Py_Initialize();
    moduleMainString = PyString_FromString("__main__");
    moduleMain = PyImport_Import(moduleMainString);

    PyRun_SimpleString(
        "import math                                                        \n"\
        "def mul(a, b):                                                     \n"\
        "   return a * b                                                    \n"\
        "                                                                   \n"\
        "def erlangB(E, M):                                                 \n"\
        "   InversoProbBloqueio = 1.0                                       \n"\
        "   for i in range(1, M):                                           \n"\
        "       InversoProbBloqueio = 1.0 + ((i / E) * InversoProbBloqueio) \n"\
        "   Bloqueio = 1.0 / InversoProbBloqueio                            \n"\
        "   return Bloqueio * 100                                           \n"\
        "                                                                   \n"\
        "def erlangC(E, M):                                                 \n"\
        "    ePower = E**M                                                  \n"\
        "    mFactorial = math.factorial(M)                                 \n"\
        "    X = ePower / mFactorial * (M/(M-E))                            \n"\
        "    Y = 0                                                          \n"\
        "    for i in range(0, M):                                          \n"\
        "        a = E**i                                                   \n"\
        "        b = math.factorial(i)                                      \n"\
        "        Y = Y + (a/b)                                              \n"\
        "    return (X / ((X+Y))) * 100                                     \n"\
        "                                                                   \n"\
        "def ocupacaoVia(E, M):                                             \n"\
        "    return (E/M) * 100                                             \n"\
        "                                                                   \n"\
        "def faixasRequeridas(M, Fator):                                    \n"\
        "    return (M/(1 - (Fator/100)))                                   \n"\
        "                                                                   \n"\
        "def nivelServico(B, M , E, ANT, MediaDuracao):                     \n"\
        "    C = -((M-E) * ANT/MediaDuracao)                                \n"\
        "    C = math.pow(math.e, C)                                        \n"\
        "    Resultado = 1 - (B * C)                                        \n"\
        "    return Resultado * 100                                         \n"\
    );
}

void PyC::desalocarPy()
{
    Py_DECREF(func);
    Py_DECREF(args);
    Py_DECREF(result);
}

double PyC::calcularBloqueio(double erlang, long slot)
{
    PyObject *func = PyObject_GetAttrString(moduleMain, "erlangB");
    PyObject *args = PyTuple_Pack(2, PyFloat_FromDouble(erlang), PyLong_FromDouble(slot));

    PyObject *result = PyObject_CallObject(func, args);

    return PyFloat_AsDouble(result);
}

double PyC::calcularProbEspera(double erlang, long slot)
{
    func = PyObject_GetAttrString(moduleMain, "erlangC");
    args = PyTuple_Pack(2, PyFloat_FromDouble(erlang), PyLong_FromDouble(slot));

    result = PyObject_CallObject(func, args);

    return PyFloat_AsDouble(result);
}

PyC::~PyC()
{
    Py_Finalize();
}
