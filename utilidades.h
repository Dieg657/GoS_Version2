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
    int *geradorDuracaoVelocidade(int velocidade, int comprimentoVia, int *qtdeMinutos);
    long int calcularAgentes(int divisao, int slot);

};

#endif // UTILIDADES_H
