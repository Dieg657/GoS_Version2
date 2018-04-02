#include "via.h"

void via::distribuicaoPoissonEExponencial(int minutosSimulados, int velocidadeVia, int comprimentoVia)
{
    /*
     */
    Utilidades * utilidades = new Utilidades();
    time_t now = time(NULL);
    struct tm tempo_carro;
    int qtdeMinutos = 0; int * vet = NULL; // Duração dos Veiculos na Pista
    vet = utilidades->geradorDuracaoVelocidade(velocidadeVia,comprimentoVia,&qtdeMinutos); //Carrega vetor com as informações de tempo de duração
    int id = 0;
    /* Estrutura da Distribuição
     * 1º - Distribuição dos Minutos a serem simulados
     * 2º - Distribuição da duração dos veiculos na pista baseada na velocidade e comprimento da via, sendo as duas ultimas aleatórias!
     * 3º - Distribuição dos Segundos de origem.
    */

    const int carros = 10000;  // Numero de Carros a serem gerados

    int vetorMinutos[minutosSimulados]={};
    for (int i = 0; i < minutosSimulados; i++) {
        vetorMinutos[i] = (i+1);
    }

    /* Tempo Origem - Minuto */
    std::default_random_engine geradorMinuto;
    std::exponential_distribution<double> distribuicaoMinuto((minutosSimulados)/2);
    /* Tempo Origem - Segundo */
    std::default_random_engine geradorSegundo;
    std::poisson_distribution<int> distribuicaoSegundo(20); //Media de 20 segundos para aparecer na via
    /*Duracao*/
    default_random_engine geradorDuracaoTempoVia;
    exponential_distribution<double> distribuicaoDuracaoTempoVia(0.5); //Duração dos carros está entre 50% do tempo de circulação

    for (int i=0; i<carros; ++i) {
      tempo_carro = *localtime(&now);
      tempo_carro.tm_sec = 0;
      double minuto = distribuicaoMinuto(geradorMinuto);
      int segundo = distribuicaoSegundo(geradorSegundo);
      double duracaoNaVia = distribuicaoDuracaoTempoVia(geradorDuracaoTempoVia);

      if (minuto < 1.0) { // Menor que 100% do tempo de circulação
          //cout << "Posição do vetor: " << int(minutosSimulados*minuto) << ", minuto gerado: " << vetorMinutos[int(minutosSimulados*minuto)] << endl;
          tempo_carro.tm_min += vetorMinutos[int(minutosSimulados*minuto)];
      }

      if(segundo < 60){// Menor que 60 segundos
          //cout << "Segundo gerado:" << segundo << endl;
          tempo_carro.tm_sec += segundo;
      }

      if(duracaoNaVia < qtdeMinutos){
          objVeiculo = new veiculo(1,mktime(&tempo_carro),vet[int(duracaoNaVia)]);
          filaVeiculos.push_back(objVeiculo);
          objVeiculo = NULL;
          id++;
      }

    }
}

via::via(double velocidadeDaVia, int tamanhoViaEmMetros, int divisaoSlotsVia, int tempoSimulacao)
{
    tamanho = tamanhoViaEmMetros;
    divisao = tamanho / divisaoSlotsVia;
    velocidadeVia = velocidadeDaVia;
    tempoSim = tempoSimulacao;
    objVeiculo = NULL;
}


via::~via()
{
}

void via::inserirCarroVia()
{
    /*
        1º Verifica se todos os slots da via estão cheios.
    */
    if (verificaViaCheia()) {
       /* Aguarda um slot ser liberado */
    }
    else {
        /*
         * 2º Se a fila tiver slot vago o veiculo com tempo horario de incidencia na via igual ao tempo atual (relogio) é inserido na via
         * do contrário irá esperar até poder aparecer na via!
         */
        while(verificaCarroFila() == true && verificaViaCheia() == false){
            /* Se a diferença de tempo é igual a 0, é a hora do carro "aparecer" na via */
            if(difftime(tempoAtual, filaVeiculos.back()->getTime()) >= 0){
                veiculos.push_back(filaVeiculos.back());
                filaVeiculos.pop_back();
            }
        }
    }
}

void via::atualizarTempPermanencia()
{
    /*
     * Atualiza o tempo de permanencia dos carros que estão usando os slots de tempo
     */
    for (auto it = veiculos.begin(); it != veiculos.end(); it++) {
        (*it)->atualizarPermanencia();
    }
}

void via::adicionarTempoAtraso()
{
    for (auto it = filaVeiculos.begin(); it != filaVeiculos.end(); it++) {
        (*it)->adicionarAtraso();
    }
}

void via::retirarCarroVia()
{
    /*
        Retira carro da via com o tempo de duração expirado
    */
    for (unsigned int i = 0; i < veiculos.size(); i++) {
        if(veiculos[i]->getPermanenciaVia() <= 0){
            veiculos[i]->setHoraSaida();
            trafegaram.push_back(veiculos[i]);
            veiculos.pop_back();
        }
    }
}

bool via::verificaViaCheia()
{
    return veiculos.size() >= (unsigned int)(divisao);
}

bool via::verificaCarroFila()
{
    return filaVeiculos.size() > 0;
}

std::vector<veiculo *> * via::getVeiculos()
{
    return &veiculos;
}

std::vector<veiculo *> *via::getTrafegaram()
{
    return &trafegaram;
}

void via::gerarVeiculos(int minutosSimulados, int velocidadeVia, int comprimentoVia)
{
    distribuicaoPoissonEExponencial(minutosSimulados, velocidadeVia, comprimentoVia);
    sort(filaVeiculos.begin(),filaVeiculos.end(),[](const veiculo *a, const veiculo *b){return difftime(a->tempoOrig, b->tempoOrig) > 0;});
    sort(filaVeiculos.begin(),filaVeiculos.end(),[](const veiculo *a, const veiculo *b){return difftime(a->tempoOrig, b->tempoOrig) > 0;});

}

void via::iniciarSimulacao()
{
    /*
     * Gerar os carros
     */
    gerarVeiculos(tempoSim,velocidadeVia,tamanho);

    tempoAtual = time(NULL);
    inicioSim = *localtime(&tempoAtual);
    termSim = inicioSim;
    termSim.tm_min += tempoSim;

    double aux = difftime(mktime(&termSim),tempoAtual);
    int sec = 0;
    while(difftime(mktime(&termSim),tempoAtual) > 0){
        if(aux != difftime(mktime(&termSim),tempoAtual)){
            sec++; aux = difftime(mktime(&termSim),tempoAtual);
            cout << "Segundos passados: " << sec << endl;
            inserirCarroVia();
            atualizarTempPermanencia();
            adicionarTempoAtraso();
            retirarCarroVia();
        }else{
            /*Não faz nada até o proximo segundo*/
        }

        time(&tempoAtual);
    }
}
