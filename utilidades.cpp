#include "utilidades.h"

Utilidades::Utilidades()
{

}

long double Utilidades::ASA(long double divisao, long double erlang, long double tempoMedioPermanencia, double erlangC)
{
    long double res = ((erlangC * tempoMedioPermanencia) / (divisao * (1 - ocupacaoVia(erlang,divisao))));

    return res;
}

long double Utilidades::nivelServico(long double tempoDesejado, long double divisao, long double erlang, long double tempoMedioPermanencia, double erlangC)
{
    long double res = 1 - (erlangC * exp(((divisao-erlang)*(tempoDesejado/tempoMedioPermanencia)) * (-1)));

    return res;
}

int * Utilidades::geradorDuracaoVelocidade(int velocidade, int comprimentoVia, int * qtdeMinutos)
{
    int k = 0;
    for (int i = (velocidade - (velocidade*0.1)); i <= (velocidade + (velocidade*0.1)); i++) {
        k++;
    }

    int * vetorMinutos = new int[k];
    *qtdeMinutos = k;
    k = 0;
    for (int i = (velocidade - (velocidade*0.1)); i < (velocidade + (velocidade*0.1)); i++) {
        vetorMinutos[k] = comprimentoVia / (double)(i/3.6);
        k++;
    }
    return vetorMinutos;
}

long double Utilidades::erlang(long double qtdVeiculo, long double tempoSimulacao, long double mediaDuracaoVeiculosVia)
{

    long double lambda = qtdVeiculo/(tempoSimulacao*60);
    long double erlangNum = lambda * mediaDuracaoVeiculosVia;

    return erlangNum;
}

long double Utilidades::calcularAgentes(int divisao, int slots)
{
    return divisao * slots;
}

long double Utilidades::fatorial(int x)
{
    long double aux = 0.0;
    if(x == 0){
        aux = 1;
    }else{
        aux = x;
        while(x > 1){
            aux = aux * (x-1);
            x -= 1;
            cout << aux << endl;
        }
    }
    return aux;
}

long double Utilidades::ocupacaoVia(long double intensTrafego, long double divisao)
{
    return intensTrafego/divisao;
}

