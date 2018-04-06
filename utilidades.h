#ifndef UTILIDADES_H
#define UTILIDADES_H
#include "header.hpp"

class Utilidades
{
private:
    long double ocupacaoVia(long double intensTrafego, long double divisao);
    void distribuicaoPoissonEExponencial(int *id, int minutosSimulados, int velocidadeVia, int comprimentoVia);
public:
    long double fatorial(int x);
    Utilidades();
    long double erlangB(long double divisao, long double erlang);
    long double erlangC(long double divisao, long double erlang);
    long double ASA(long double divisao, long double erlang, long double tempoMedioPermanencia, double erlangC);
    long double nivelServico(long double tempoDesejado, long double divisao, long double erlang, long double tempoMedioPermanencia, double erlangC);
    int *geradorDuracaoVelocidade(int velocidade, int comprimentoVia, int *qtdeMinutos);
    long double erlang(long double qtdVeiculo, long double tempoSimulacao, long double mediaDuracaoVeiculosVia);
    long double calcularAgentes(int divisao, int slots);

};

#endif // UTILIDADES_H
