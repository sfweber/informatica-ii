/* ej06_insertar_primero · main.cpp — insertarPrimero en 3 pasos (con el setter setSig de Nodo) */
#include <iostream>
#include "lista.h"

int main ()
{
    Lista lista;
    lista.crearLista ();
    lista.insertarPrimero (-123);  // queda adelante de todos
    lista.recorrerLista ();
    return 0;
}
