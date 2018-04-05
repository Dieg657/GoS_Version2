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
    long int id; //ID Veiculos
    int tamanho; //Tamanho da Via em Metros
    unsigned int divisao; //Divisão em Metros da Via para cada Veiculo
    double velocidadeVia; //Velocidade em Km/H
    int faixas; //Quantidade de faixas disponíveis para tráfego na via
    time_t tempoAtual;
    struct tm inicioSim;
    struct tm termSim;
    Utilidades utilidades;
    veiculo * objVeiculo;
    vector<veiculo*> veiculosVia;
    vector<veiculo*> filaVeiculos;
    vector<veiculo*> trafegaram;
    void distribuicaoPoissonEExponencial(int minutosSimulados, int velocidadeVia, int comprimentoVia);
    void gerarVeiculos(int minutosSimulados, int velocidadeVia, int comprimentoVia);
    void inserirCarroVia();
    void tiraDaFila();
    void atualizarTempPermanencia();
    void adicionarTempoAtraso();
    void retirarCarroVia();
    bool verificaViaCheia();
    bool verificaCarroFila();
public:
    via();
    void setAtributosVia(double velocidadeDaVia, int tamanhoViaEmMetros, int qtdeFaixasVia);
    void setAtributosCarro(int divisaoSlotsVia, int tempoSimulacao);
    std::vector<veiculo*> *getVeiculosNaVia();
    std::vector<veiculo*> *getTrafegaram();
    std::vector<veiculo *> *getVeiculosNaFila();
    void iniciarSimulacao(int tempoSimulacao);
    long double mediaEsperaNaVia();
    long double mediaTempoTrafegado();
    ~via();
};


#endif // VIA_H
