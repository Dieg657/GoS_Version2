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

    return 0;

}
