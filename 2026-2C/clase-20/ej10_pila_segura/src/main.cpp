/* ej10_pila_segura · main.cpp — push/pop controlan llena/vacia; borrarPila */
#include <iostream>
#include "pila.h"

int main ()
{
    Pila miPila (3);

    for (int i = 1 ; i <= 4 ; i++)   // el cuarto no entra: aviso
        miPila.push (i);
    for (int i = 1 ; i <= 4 ; i++)   // el cuarto pop no tiene que sacar: aviso y -1
        std::cout << miPila.pop () << '\t';
    std::cout << '\n';

    miPila.push (7);
    miPila.borrarPila ();
    std::cout << "Despues de borrarPila, vacia? " << (miPila.isEmpty () ? "si" : "no") << '\n';
    return 0;
}
