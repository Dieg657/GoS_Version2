#include "header.hpp"
#include "veiculo.h"
#include "via.h"
#include "utilidades.h"


using namespace std;

int main()
{
    via *a = new via(60,500,6,2);
    a->iniciarSimulacao();

    cout << "Carros que trafegaram: " << a->getTrafegaram()->size() << endl;
    cout << "Carros que ainda permanecem na via: " << a->getVeiculosNaVia()->size() << endl;
    cout << "Carros que ainda estão na fila: " << a->getVeiculosNaFila()->size() << endl;

    /*
    time_t agora = time(NULL);
    struct tm tempo1 = *localtime(&agora);
    struct tm tempo2 = tempo1;

    tempo2.tm_sec += 3;

    cout << "Diferenca de tempo: " << difftime(mktime(&tempo2), mktime(&tempo1)) << endl;
    */
    return 0;

}


/*
 * difftime - Retorna a diferença entre o tempo de origem e o tempo atual, e também verifica quanto tempo se passou desde a simulação em segundos
 */

/*

  */
