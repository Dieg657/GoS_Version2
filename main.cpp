#include "header.hpp"
#include "veiculo.h"
#include "via.h"
#include "utilidades.h"
#include "pycalculos.h"

using namespace std;
using namespace boost::python;

int main()
{
    via *a = new via(60,500,6,1,1,500);
    a->iniciarSimulacao(2);

    /*PyC a;

    cout <<  "Bloqueio: " << a.calcularBloqueio(10,11) << "%" << endl;
    cout <<  "Probabilidade de espera: " << a.calcularProbEspera(10,11) << "%" << endl;*/
    return 0;

}
