/* ej07_insertar_ultimo · main.cpp — getUltimo (nullptr si vacia) + insertarUltimo (delega en insertarPrimero si vacia) */
#include <iostream>
#include "lista.h"

int main ()
{
    Lista lista;
    lista.crearLista ();
    lista.insertarPrimero (-123);
    lista.insertarUltimo (666);     // camina hasta el ultimo y lo engancha
    lista.recorrerLista ();

    Lista otra;
    otra.insertarUltimo (666);      // en una lista vacia: el ultimo es el primero
    otra.recorrerLista ();
    return 0;
}
