/* ej09_pila · main.cpp — Pila con vector en el heap, push/pop sin controles */
#include <iostream>
#include "pila.h"

int main ()
{
    Pila miPila (3);                 // el tamano se decide aca, en ejecucion

    miPila.push ('R');
    miPila.push ('I');
    miPila.push ('O');
    std::cout << "Entrada: RIO" << '\n' << "Salida:  ";
    while (!miPila.isEmpty ())
        std::cout << (char) miPila.pop ();
    std::cout << '\n';
    return 0;
}
