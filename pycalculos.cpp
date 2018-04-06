#include "pycalculos.h"

PyC::PyC()
{
    Py_Initialize();
    moduleMainString = PyString_FromString("__main__");
    moduleMain = PyImport_Import(moduleMainString);

    PyRun_SimpleString(
        "import math                                                        \n"\
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
        "                                                                   \n"\
        "def erlang(C, T, Med):                                             \n"\
        "    X = (C/(T*60))                                                 \n"\
        "    X = X / Med                                                    \n"\
        "    return X                                                       \n"\
    );
}

void PyC::desalocarPy()
{
    Py_DECREF(func);
    Py_DECREF(args);
    Py_DECREF(result);
}

double PyC::erlang(int qtdCarro, int tempoSim, long double medVec)
{
    PyObject *func = PyObject_GetAttrString(moduleMain, "erlang");
    PyObject *args = PyTuple_Pack(3, PyLong_FromLong(qtdCarro), PyLong_FromLong(tempoSim), PyFloat_FromDouble(medVec));

    PyObject *result = PyObject_CallObject(func, args);

    return PyFloat_AsDouble(result);
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

double PyC::calcularOcupacaoVia(double erlang, long slot){
    func = PyObject_GetAttrString(moduleMain, "ocupacaoVia");
    args = PyTuple_Pack(2, PyFloat_FromDouble(erlang), PyLong_FromDouble(slot));

    result = PyObject_CallObject(func, args);

    return PyFloat_AsDouble(result);
}

double PyC::nivelServico(double eC, double erlang, long slot, long tempoDesejado, long tempoSimulado){
    func = PyObject_GetAttrString(moduleMain, "nivelServico");
    args = PyTuple_Pack(5, PyFloat_FromDouble(eC), PyFloat_FromDouble(erlang), PyLong_FromLong(slot), PyLong_FromLong(tempoDesejado), PyLong_FromLong(tempoSimulado*60));

    result = PyObject_CallObject(func, args);

    return PyFloat_AsDouble(result);
}

PyC::~PyC()
{
    Py_Finalize();
}
