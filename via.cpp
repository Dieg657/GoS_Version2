#include "via.h"

void via::distribuicaoPoissonEExponencial(int minutosSimulados, int velocidadeVia, int comprimentoVia)
{
    /*
     */
    time_t now = time(NULL);
    struct tm tempo_carro;
    int qtdeMinutos = 0; // Duração dos veiculosVia na Pista
    vet = utilidades.geradorDuracaoVelocidade(velocidadeVia,comprimentoVia,&qtdeMinutos); //Carrega vetor com as informações de tempo de duração

    /* Estrutura da Distribuição
     * 1º - Distribuição dos Minutos a serem simulados
     * 2º - Distribuição da duração dos veiculos na pista baseada na velocidade e comprimento da via, sendo as duas ultimas aleatórias!
     * 3º - Distribuição dos Segundos de origem.
    */


    const int t_vecMinutos = minutosSimulados;
    int *vetorMinutos = new int[t_vecMinutos];

    for (int i = 0; i < minutosSimulados; i++) {
        vetorMinutos[i] = (i+1);
        minutoGrafico[(i+1)] = 0;
    }

    /* Tempo Origem - Minuto */
    std::default_random_engine geradorMinuto;
    std::poisson_distribution<int> distribuicaoMinuto(minutosSimulados);
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



      if (minuto < minutosSimulados) { // Menor que 100% do tempo de circulação
          //cout << "Posição do vetor: " << int(minutosSimulados*minuto) << ", minuto gerado: " << vetorMinutos[int(minutosSimulados*minuto)] << endl;
          tempo_carro.tm_min += vetorMinutos[int(minuto)];

          minutoGrafico[minuto] += 1;

          //cout << "Minuto: " << minuto+1 << ", vezes: " << minutoGrafico[minuto] << endl;
      }

      if(segundo < 60){// Menor que 60 segundos
          //cout << "Segundo gerado:" << segundo << endl;
          tempo_carro.tm_sec += segundo;
          segundosGrafico[segundo] += 1;
          //cout << "Segundo: " << segundo << ", vezes: " << segundosGrafico[segundo] << endl;
      }

      if(duracaoNaVia < qtdeMinutos){ 
          objVeiculo = new veiculo(id,mktime(&tempo_carro),vet[int(duracaoNaVia)]);
          duracaoGrafico[duracaoNaVia] += 1;
          filaVeiculos.push_back(objVeiculo);
          id += 1;
      }
    }
}

via::via(double velocidadeDaVia, int tamanhoViaEmMetros, int divisaoSlotsVia, int tempoSimulacao, int qtdeFaixasVia, int qtdCarros)
{
    vet = nullptr;
    vetAux = nullptr;
    faixas = qtdeFaixasVia;
    tamanho = tamanhoViaEmMetros;
    divisao = tamanho / divisaoSlotsVia;
    velocidadeVia = velocidadeDaVia;
    tempoSim = tempoSimulacao;
    this->carros = qtdCarros;
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

void via::iniciarSimulacao(int tempoSimulacao)
{
    /*
     * Gerar os carros
     */
    tempoSim = tempoSimulacao;
    gerarVeiculos(tempoSimulacao,velocidadeVia,tamanho);
    cout << "Gerou os carros! " << endl;

    tempoAtual = time(NULL);
    inicioSim = *localtime(&tempoAtual);
    termSim = inicioSim;
    termSim.tm_min += tempoSimulacao;

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

        }

        time(&tempoAtual);
    }

    duracaoGraf();
    minutosGraf();
    segsGraf();

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
    long double numErlangs = utilidades.erlang(veiculos,tempoSim,mediaTempoTrafegado());
    long double divisaoVias = utilidades.calcularAgentes(faixas,divisao);
    cout << "Erlangs: " << numErlangs << endl;
    cout << "Num. Div. da Via: " << divisaoVias << endl;
    cout << "Bloqueio: " << python.calcularBloqueio(numErlangs,divisaoVias) << "%" << endl;
    cout << "Prob. de Espera: " << python.calcularProbEspera(numErlangs,divisaoVias) << "%" << endl;
    cout << "Ocupação da Via: " << python.calcularOcupacaoVia(numErlangs,divisaoVias) << "%" << endl;
    cout << "Nível de Serviço (GoS): " << python.nivelServico(python.calcularBloqueio(numErlangs,divisaoVias),numErlangs,divisaoVias,15,60) << "%" << endl;
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

void via::minutosGraf()
{
    ofstream minuto("minuto.csv");
    const char *bom = "\xef\xbb\xbf";
    minuto << bom;
    minuto << "Minuto (Em que irá aparecer) ; Vezes de selecionado" << endl;
    for (int i = 0; i < tempoSim; i++) {
        minuto << i+1 << " ; " << minutoGrafico[i] << endl;
    }
    minuto.close();

}

void via::segsGraf()
{
    ofstream segundo("segundo.csv");
    const char *bom = "\xef\xbb\xbf";
    segundo << bom;
    segundo << "Segundo (Em que irá aparecer) ; Vezes de selecionado" << endl;
    for (int i = 1; i < 60; i++) {
        segundo << i << " ; " << segundosGrafico[i] << endl;
    }
    segundo.close();
}

void via::duracaoGraf()
{
    int k = 0;
    ofstream duracao("duracao.csv");
    const char *bom = "\xef\xbb\xbf";
    duracao << bom;
    duracao << "Duração (Em segundos) ; Vezes de selecionado" << endl;
    for (int i = velocidadeVia - (velocidadeVia *0.1); i <= velocidadeVia + (velocidadeVia * 0.10); i++) {
        duracao << i << " ; " << duracaoGrafico[k] << endl;
        k++;
    }
    duracao.close();
}
