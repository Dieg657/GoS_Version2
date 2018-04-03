#include "via.h"

void via::distribuicaoPoissonEExponencial(int minutosSimulados, int velocidadeVia, int comprimentoVia)
{
    /*
     */
    time_t now = time(NULL);
    struct tm tempo_carro;
    int qtdeMinutos = 0; int * vet = NULL; // Duração dos veiculosVia na Pista
    vet = utilidades.geradorDuracaoVelocidade(velocidadeVia,comprimentoVia,&qtdeMinutos); //Carrega vetor com as informações de tempo de duração
    /* Estrutura da Distribuição
     * 1º - Distribuição dos Minutos a serem simulados
     * 2º - Distribuição da duração dos veiculos na pista baseada na velocidade e comprimento da via, sendo as duas ultimas aleatórias!
     * 3º - Distribuição dos Segundos de origem.
    */

    const int carros = 1000;  // Numero de Carros a serem gerados

    int t_vecMinutos = minutosSimulados;
    int *vetorMinutos = new int[t_vecMinutos];
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

via::via(double velocidadeDaVia, int tamanhoViaEmMetros, int divisaoSlotsVia, int tempoSimulacao, int qtdeFaixasVia)
{
    faixas = qtdeFaixasVia;
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
    veiculosVia.clear();
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
                tiraDaFila();
                cout << "Inseriu carro na via!" << endl;
        }
        //cout << "Diferenca: " << difftime(tempoAtual, filaVeiculos.back()->getTime()) << ", ID: " << filaVeiculos.back()->getID() << endl;
    }
}

void via::tiraDaFila()
{
    if(difftime(filaVeiculos.back()->getTime(),tempoAtual) <= 0){
        if(verificaViaCheia()){
            cout << "A via está cheia!" << endl;
        }else{
            veiculosVia.push_back(filaVeiculos.back()); //Coloca na via
            filaVeiculos.pop_back(); // Tira da Fila
        }
    }
}

void via::atualizarTempPermanencia()
{
    /*
     * Atualiza o tempo de permanencia dos carros que estão usando os slots de tempo
     */
    for (auto it = veiculosVia.begin(); it != veiculosVia.end(); it++) {
        (*it)->atualizarPermanencia();
    }
}

void via::adicionarTempoAtraso()
{
    for (auto it = filaVeiculos.begin(); it != filaVeiculos.end(); it++) {
        if(difftime((*it)->getTime(),tempoAtual) < 0)
            (*it)->adicionarAtraso();
    }
}

void via::retirarCarroVia()
{
    /*
        Retira carro da via com o tempo de duração expirado
    */
    int i = 0;
    if(veiculosVia.size() > 0){
        cout << "Via com carros!" << endl;
        for (auto it = veiculosVia.begin(); it != veiculosVia.end() && veiculosVia.size() > 0; it++) {
            if((*it)->getPermanenciaVia() < 0){
                (*it)->setHoraSaida();
                trafegaram.push_back((*it));
                veiculosVia.erase(veiculosVia.begin() + i);
            }
            i++;
        }
        cout << "Analisou retirada de carros!" << endl;
    }else{
        cout << "Via vazia!" << endl;
    }
}

bool via::verificaViaCheia()
{
    return veiculosVia.size() == divisao;
}

bool via::verificaCarroFila()
{
    return filaVeiculos.size() > 0;
}

std::vector<veiculo *> * via::getVeiculosNaVia()
{
    return &veiculosVia;
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
    termSim.tm_min += tempoSim+1;

    double aux = difftime(mktime(&termSim),tempoAtual);
    int sec = 0;
    while(difftime(mktime(&termSim),tempoAtual) > 0){
        if(aux != difftime(mktime(&termSim),tempoAtual)){
            sec++; aux = difftime(mktime(&termSim),tempoAtual);
            cout << "Segundos passados: " << aux << endl;
            inserirCarroVia();
            atualizarTempPermanencia();
            adicionarTempoAtraso();
            retirarCarroVia();
        }else{
            /*Não faz nada até o proximo segundo*/
        }

        time(&tempoAtual);
    }

    /*
     * N - Definido pela multiplicação do numero de faixas de rolamento pela quantidade de slots disponíveis na via!
     */

    cout << "Carros que trafegaram: " << getTrafegaram()->size() << endl;
    cout << "Carros que ainda permanecem na via: " << getVeiculosNaVia()->size() << endl;
    cout << "Carros que ainda estão na fila: " << getVeiculosNaFila()->size() << endl;
    cout << "Media do tempo de espera: " << mediaEsperaNaVia() << " em segundos!" << endl;
    cout << "Media do tempo trafegado na via: " << mediaTempoTrafegado() << " em segundos!" << endl;

    /* Calcular Bloqueio, Probabilidade de Espera, Nível de Serviço*/
    long int veiculos = 0;
    veiculos = getTrafegaram()->size() + getVeiculosNaVia()->size();
    long double numErlangs = utilidades.erlang(veiculos,tempoSim+1,mediaTempoTrafegado());
    long double divisaoVias = utilidades.calcularAgentes(faixas,divisao);
    cout << "Divisao: " << divisaoVias << endl;
    printf("Bloqueio: %.2Lf", utilidades.erlangB(divisaoVias,numErlangs));
    printf("Probabilidade de espera: %.2Lf\n", utilidades.erlangC(divisaoVias,numErlangs));
    printf("Tempo medio para entrar na via: %.2Lf seg(s)\n",utilidades.ASA(divisaoVias,numErlangs,mediaTempoTrafegado()));
    printf("O nivel de servico da via e: %.2Lf\n", utilidades.nivelServico(20,divisaoVias,numErlangs,mediaTempoTrafegado()));
}

long double via::mediaEsperaNaVia()
{
    long double espera = 0;
    int contador = 0;
    for (auto it = filaVeiculos.begin(); it != filaVeiculos.end(); it++) {
        if((*it)->getAtraso() > 0){
            espera += (*it)->getAtraso();
        }
        contador++;
    }

    for (auto it = veiculosVia.begin(); it != veiculosVia.end(); it++) {
        if((*it)->getAtraso() > 0){
            espera += (*it)->getAtraso();
        }
        contador++;
    }

    for (auto it = trafegaram.begin(); it != trafegaram.end(); it++) {
        if((*it)->getAtraso() > 0){
            espera += (*it)->getAtraso();
        }
        contador++;
    }

    return espera/contador;
}

long double via::mediaTempoTrafegado()
{
    int contador = 0;
    long double tempoGasto = 0;

    for (auto it = veiculosVia.begin(); it != veiculosVia.end(); it++) {
        tempoGasto += (*it)->getDuracaoDoVeiculoNaVia();
        contador++;
    }

    for (auto it = trafegaram.begin(); it != trafegaram.end(); it++) {
        tempoGasto += (*it)->getDuracaoDoVeiculoNaVia();
        contador++;
    }

    return tempoGasto/contador;
}
