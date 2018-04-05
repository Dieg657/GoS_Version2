#include "header.hpp"
#include "veiculo.h"
#include "via.h"
#include "utilidades.h"
#include "pycalculos.h"

using namespace std;
using namespace boost::python;

int main()
{
    Py_Initialize();
    PyC * a = new PyC();


    cout << setprecision(1) << fixed << "Bloqueio: " << a->calcularBloqueio(10,11) << "%" << endl;
    cout << setprecision(1) << fixed << "Probabilidade de espera: " << a->calcularProbEspera(10,11) << "%" << endl;
    return 0;

}
