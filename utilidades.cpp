#include "utilidades.h"

Utilidades::Utilidades()
{

}

int *Utilidades::geradorDuracaoVelocidade(int velocidade, int comprimentoVia, int *qtdeMinutos)
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

long int Utilidades::calcularAgentes(int divisao, int slot)
{
    return divisao * slot;
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
