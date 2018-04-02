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
    /* Estrutura da Distribuição
     * 1º - Distribuição dos Minutos a serem simulados
     * 2º - Distribuição da duração dos veiculos na pista baseada na velocidade e comprimento da via, sendo as duas ultimas aleatórias!
     * 3º - Distribuição dos Segundos de origem.
    */

    const int carros = 1000;  // Numero de Carros a serem gerados

	const int t_vecMinutos = minutosSimulados;
    int vetorMinutos[t_vecMinutos]={};
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

    for (long int i=0; i<carros; i++) {
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
          objVeiculo = new veiculo(id,mktime(&tempo_carro),vet[int(duracaoNaVia)]);
          filaVeiculos.push_back(objVeiculo);
          id += 1;
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
    id = 0;
    tempoAtual = time(NULL);
}


via::~via()
{
    delete[] objVeiculo;
    objVeiculo = NULL;
    veiculos.clear();
    filaVeiculos.clear();
    trafegaram.clear();
}

void via::inserirCarroVia()
{
    /*
        1º Verifica se todos os slots da via estão cheios.
    */
    if (verificaViaCheia()) {
       /* Aguarda um slot ser liberado */
        //cout << "Diferenca: " << difftime(tempoAtual, filaVeiculos.back()->getTime()) << ", ID: " << filaVeiculos.back()->getID() << endl;
    }
    else {
        /*
         * 2º Se a fila tiver slot vago o veiculo com tempo horario de incidencia na via igual ao tempo atual (relogio) é inserido na via
         * do contrário irá esperar até poder aparecer na via!
         */
        while(verificaViaCheia() == false){
            /* Se a diferença de tempo é igual a 0, é a hora do carro "aparecer" na via */
            if(difftime(filaVeiculos.back()->getTime(),tempoAtual) <= 0){
                veiculos.push_back(filaVeiculos.back()); //Coloca na via
                filaVeiculos.pop_back(); // Tira da Fila
            }
        }
        //cout << "Diferenca: " << difftime(tempoAtual, filaVeiculos.back()->getTime()) << ", ID: " << filaVeiculos.back()->getID() << endl;
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
        //if(difftime())
        (*it)->adicionarAtraso();
    }
}

void via::retirarCarroVia()
{
    /*
        Retira carro da via com o tempo de duração expirado
    */
    if(veiculos.size() > 0){
        cout << "Via com carros!" << endl;
        for (auto it = veiculos.begin(); it != veiculos.end() && veiculos.size() > 0; it++) {
            if((*it)->getPermanenciaVia() <= 0){
                (*it)->setHoraSaida();
                trafegaram.push_back((*it));
                veiculos.pop_back();
                cout << "Carro retirado!" << endl;
            }
        }
        cout << "Analisou retirada de carros!" << endl;
    }else{
        cout << "Via vazia!" << endl;
    }
}

bool via::verificaViaCheia()
{
    return !veiculos.empty();
}

bool via::verificaCarroFila()
{
    return filaVeiculos.size() > 0;
}

std::vector<veiculo *> * via::getVeiculosNaVia()
{
    return &veiculos;
}

std::vector<veiculo *> *via::getTrafegaram()
{
    return &trafegaram;
}

std::vector<veiculo *> *via::getVeiculosNaFila()
{
    return &filaVeiculos;
}

void via::gerarVeiculos(int minutosSimulados, int velocidadeVia, int comprimentoVia)
{
    distribuicaoPoissonEExponencial(minutosSimulados, velocidadeVia, comprimentoVia);
    sort(filaVeiculos.begin(),filaVeiculos.end(),[](const veiculo *a, const veiculo *b){return difftime(a->tempoOrig, b->tempoOrig) > 0.0;});
}

void via::iniciarSimulacao()
{
    /*
     * Gerar os carros
     */

    gerarVeiculos(tempoSim,velocidadeVia,tamanho);
    cout << "Gerou os carros! " << endl;

    tempoAtual = time(NULL);
    inicioSim = *localtime(&tempoAtual);
    termSim = inicioSim;
    termSim.tm_min += tempoSim;

    double aux = difftime(mktime(&termSim),tempoAtual);
    int sec = 0;
    while(difftime(mktime(&termSim),tempoAtual) > 0){
        if(aux != difftime(mktime(&termSim),tempoAtual)){
            sec++; aux = difftime(mktime(&termSim),tempoAtual);
            cout << "Segundos passados: " << aux << endl;
            inserirCarroVia();
            cout << "Inseriu carros na via! " << endl;
            atualizarTempPermanencia();
            //cout << "Atualizou a permanencia dos carros na via! " << endl;
            adicionarTempoAtraso();
            //cout << "Adicionou tempo de atraso dos carros na via! " << endl;
            retirarCarroVia();
            //cout << "Retirou carros da via! " << endl;
        }else{
            /*Não faz nada até o proximo segundo*/
        }

        time(&tempoAtual);
    }
}
