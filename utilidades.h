#ifndef UTILIDADES_H
#define UTILIDADES_H
#include "header.hpp"

class Utilidades
{
private:
    long double fatorial(int x);
    long double numErlangB(long double faixas, long double erlang);
    long double denomErlangB(long double faixas, long double erlang);
    long double numErlangC(long double faixas, long double erlang);
    long double denomErlangC(long double faixas, long double erlang, long double numErlangC, long double ocupacaoVia);
    long double ocupacaoVia(long double intensTrafego, long double faixas);
    void distribuicaoPoissonEExponencial(int *id, int minutosSimulados, int velocidadeVia, int comprimentoVia);
public:
    Utilidades();
    long double erlangB(long double faixas, long double erlang);
    long double erlangC(long double faixas, long double erlang);
    long double ASA(long double faixas, long double erlang, long double tempoMedioPermanencia);
    long double nivelServico(long double tempoDesejado, long double faixas, long double erlang, long double tempoMedioPermanencia);
    int *geradorDuracaoVelocidade(int velocidade, int comprimentoVia, int *qtdeMinutos);
    long double erlang(long double qtdVeiculo, long double tempoSimulacao, long double mediaDuracaoVeiculosVia);
};

#endif // UTILIDADES_H
