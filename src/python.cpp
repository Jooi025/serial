#include <Python.h>

int main(){

    Py_Initialize();
    PyRun_SimpleString("print('Hello C++ from python')");
    Py_Finalize();

    return 0;
}