#include "header.hpp"
#include "veiculo.h"
#include "via.h"
#include "utilidades.h"


using namespace std;
using namespace boost::python;

int main()
{
    Py_Initialize();
     PyObject* filename = PyString_FromString((char*)"utilidades");
         PyObject* imp = PyImport_Import(filename);
         PyObject* func = PyObject_GetAttrString(imp,(char*)"someFunction");
         PyObject* args = PyTuple_Pack(1,PyString_FromString("CacheSetup"));
         PyObject* retured_value = PyObject_CallObject(func, args); // if you have arg
         double result = PyFloat_AsDouble(retured_value);
     std::cout << result << std::endl;
     Py_Finalize();




    return 0;

}
