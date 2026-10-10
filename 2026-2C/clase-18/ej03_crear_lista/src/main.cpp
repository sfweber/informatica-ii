/* ej03_crear_lista · main.cpp — crearLista: cada valor ingresado crea un nodo al comienzo */
#include <iostream>
#include "lista.h"

int main ()
{
    Lista lista;
    lista.crearLista ();           // lee valores hasta -1; cada uno queda adelante del anterior
    std::cout << "Lista creada" << '\n';
    return 0;
}
