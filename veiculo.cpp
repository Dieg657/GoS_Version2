#include "veiculo.h"

veiculo::veiculo()
{
}

veiculo::veiculo(int id, time_t tempoOrigem, int duracao)
{
    id = id;
    tempEspera = 0;
    tempoOrig = tempoOrigem;
    duracaoVeiculoVia = duracaoSeg = duracao;
}

void veiculo::adicionarAtraso()
{
    /* Um segundo de incremento*/
    tempEspera += 1;
}

void veiculo::setHoraSaida()
{
    saidaVia = time(NULL);
}

int veiculo::getAtraso()
{
    return tempEspera;
}

void veiculo::atualizarPermanencia()
{
    /* Diminui o tempo de permanencia na via */
   this->duracaoSeg--;
   cout << "Veiculo: " << id << ", ainda deve permanecer: " << duracaoSeg << endl;
}

int veiculo::getPermanenciaVia()
{
    return duracaoSeg;
}

int veiculo::getDuracaoDoVeiculoNaVia()
{
    return duracaoVeiculoVia;
}

/*
 * Seta a velocidade após retirar ele da via
 */
void veiculo::setKmPorHora(int metrosVia)
{
    double msPorSegundo = metrosVia / duracaoVeiculoVia;
    kmPorHora = msPorSegundo * 3.6;
}

int veiculo::getID()
{
    return id;
}

time_t veiculo::getTime()
{
    return tempoOrig;
}

veiculo::~veiculo()
{

}
