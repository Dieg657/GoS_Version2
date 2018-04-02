#ifndef VIA_H
#define VIA_H
#include "header.hpp"
#include "veiculo.h"
#include "utilidades.h"

using namespace std;

class veiculo;

class via
{
private:
    long int id;
    int tamanho;
    unsigned int divisao;
    double velocidadeVia;
    int tempoSim;
    time_t tempoAtual;
    struct tm inicioSim;
    struct tm termSim;
    veiculo * objVeiculo;
    vector<veiculo*> veiculos;
    vector<veiculo*> filaVeiculos;
    vector<veiculo*> trafegaram;
    void distribuicaoPoissonEExponencial(int minutosSimulados, int velocidadeVia, int comprimentoVia);
    void gerarVeiculos(int minutosSimulados, int velocidadeVia, int comprimentoVia);
    void inserirCarroVia();
    void inserirCarroVia(int id);
    void atualizarTempPermanencia();
    void adicionarTempoAtraso();
    void retirarCarroVia();
    bool verificaViaCheia();
    bool verificaCarroFila();
public:
    via(double velocidadeDaVia, int tamanhoViaEmMetros, int divisaoSlotsVia, int tempoSimulacao);
    std::vector<veiculo*> *getVeiculosNaVia();
    std::vector<veiculo*> *getTrafegaram();
    std::vector<veiculo *> *getVeiculosNaFila();
    void iniciarSimulacao();
    ~via();
};


#endif // VIA_H
