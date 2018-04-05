#include "header.hpp"
#include "veiculo.h"
#include "via.h"
#include "utilidades.h"
#include "pycalculos.h"

using namespace std;

int main()
{
    //via *a = new via(60,500,6,1,1,500);
    //a->iniciarSimulacao();

    PyC a;

    cout <<  "Bloqueio: " << a.calcularBloqueio(10,11) << "%" << endl;
    cout <<  "Probabilidade de espera: " << a.calcularProbEspera(10,11) << "%" << endl;
    return 0;

}
