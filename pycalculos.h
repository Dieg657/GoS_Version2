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

