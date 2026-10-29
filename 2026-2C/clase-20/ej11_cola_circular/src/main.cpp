/* ej11_cola_circular · main.cpp — CircQueue: el % hace circular al vector; count para llena/vacia */
#include <iostream>
#include "circqueue.h"

int main ()
{
    CircQueue miCola (5);
    std::cout << "El tamano de la cola es: " << miCola.getSize () << '\n';

    for (int i = 8 ; i <= 13 ; i++)                   // 8,9,10,11,12 entran; el 13 no: aviso
        miCola.enqueue (i);
    std::cout << "Frente: " << miCola.getFront () << '\n';

    std::cout << "Salen: ";
    for (int i = 0 ; i < 3 ; i++)
        std::cout << miCola.dequeue () << '\t';      // 8 9 10: quedan lugares libres a la izquierda
    std::cout << '\n';

    miCola.enqueue (-6);                               // da la vuelta: va al indice 0
    miCola.enqueue (-7);
    std::cout << "Salen: ";
    while (!miCola.isEmpty ())
        std::cout << miCola.dequeue () << '\t';      // 11 12 -6 -7: el orden FIFO se mantiene
    std::cout << '\n';
    miCola.dequeue ();                                 // vacia: aviso y -1
    return 0;
}
