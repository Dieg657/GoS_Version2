#include "header.hpp"
#include "veiculo.h"
#include "via.h"
#include "utilidades.h"

using namespace std;
using namespace boost::python;

int main()
{

    via *a = new via(60,500,6,1,1,500);
    a->iniciarSimulacao(2);

    /*PyC a;
    cout << "Blq " << fixed << setprecision(2) << a.calcularBloqueio(88,166) << endl;
    cout << "Pw  " << fixed << setprecision(2) << a.calcularProbEspera(88,166) << endl;
    cout << "Se  " << a.nivelServico(0.68,10,11,20,180) << endl;*/
    return 0;

}
