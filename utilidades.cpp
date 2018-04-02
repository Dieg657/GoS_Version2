#include "utilidades.h"

Utilidades::Utilidades()
{

}

long double Utilidades::erlangB(long double faixas, long double erlang)
{
    return numErlangB(faixas,erlang)/denomErlangB(faixas,erlang);
}

long double Utilidades::erlangC(long double faixas, long double erlang)
{
    long double ocupacao = ocupacaoVia(erlang, faixas);
    long double num = numErlangC(faixas,erlang);
    long double denom = denomErlangC(faixas,erlang,num,ocupacao);

    return (num / denom);
}

long double Utilidades::ASA(long double faixas, long double erlang, long double tempoMedioPermanencia)
{
    long double res = ((erlangC(faixas,erlang) * tempoMedioPermanencia) / (faixas * (1 - ocupacaoVia(erlang,faixas))));

    return res;
}

long double Utilidades::nivelServico(long double tempoDesejado, long double faixas, long double erlang, long double tempoMedioPermanencia)
{
    long double res = 1 - (erlangC(faixas,erlang) * exp(((faixas-erlang)*(tempoDesejado/tempoMedioPermanencia)) * (-1)));

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

long double Utilidades::fatorial(int x)
{
    long double aux;
    if(x == 0){
        aux = 1;
    }else{
        aux = x;
        while(x > 1){
            aux = aux * (x-1);
            x--;
        }
    }
    return aux;
}

long double Utilidades::numErlangB(long double faixas, long double erlang)
{
    long double num = pow(erlang,faixas)/fatorial(faixas);
    return num;
}

long double Utilidades::denomErlangB(long double faixas, long double erlang)
{
    long double somatorio = 0.0;

    for (int i = 0; i <= faixas; i++) {
        somatorio += pow(erlang,i)/fatorial(i);
    }

    return somatorio;
}

long double Utilidades::numErlangC(long double faixas, long double erlang)
{

    long double num = pow(erlang,faixas)/fatorial(faixas);
    return num;
}

long double Utilidades::denomErlangC(long double faixas, long double erlang, long double numErlangC, long double ocupacaoVia)
{
    long double somatorio = 0;

    for (int i = 0; i < faixas; i++) {
        somatorio += pow(erlang,i)/fatorial(i);
    }

    long double denom = (numErlangC + ((1-ocupacaoVia) * somatorio));

    return denom;
}

long double Utilidades::ocupacaoVia(long double intensTrafego, long double faixas)
{
    return intensTrafego/faixas;
}

