/* ej05_destructor · main.cpp — ~Lista libera todos los nodos */
#include <iostream>
#include "lista.h"

int main ()
{
    Lista lista;
    lista.crearLista ();
    lista.recorrerLista ();
    // al cerrar la llave del main corre ~Lista(): libera todos los nodos
    return 0;
}
