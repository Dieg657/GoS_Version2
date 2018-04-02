#ifndef VEICULO_H
#define VEICULO_H
#include "header.hpp"
#include "utilidades.h"

class veiculo
{
    int id;
    time_t saidaVia;
    int duracaoSeg;
    int tempEspera;
    int duracaoVeiculoVia;
    double kmPorHora;
public:
    time_t tempoOrig;
    veiculo();
    veiculo(int id, time_t tempoOrigem, int duracao);
    void adicionarAtraso();
    void setHoraSaida();
    int getAtraso();
    void atualizarPermanencia();
    int getPermanenciaVia();
    int getDuracaoDoVeiculoNaVia();
    void setKmPorHora(int metrosVia);
    int getID();
    time_t getTime();
    ~veiculo();
};

#endif
