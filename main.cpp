#include "header.hpp"
#include "veiculo.h"
#include "via.h"
#include "utilidades.h"


using namespace std;

int main()
{
    via *a = new via(60,500,6,1);
    a->iniciarSimulacao();
    for (auto it = a->getTrafegaram()->begin(); it != a->getTrafegaram()->end(); it++) {
            cout << "Veiculo: "<< (*it)->getID() << ", atraso de: " << (*it)->getAtraso() << endl;
    }

    return 0;

}


/*
 * difftime - Retorna a diferença entre o tempo de origem e o tempo atual, e também verifica quanto tempo se passou desde a simulação em segundos
 */

/*

  */
