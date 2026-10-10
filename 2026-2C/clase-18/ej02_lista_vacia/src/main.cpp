/* ej02_lista_vacia · main.cpp — class Lista con m_inicio = nullptr */
#include <iostream>
#include "lista.h"

int main ()
{
    Lista lista;                   // corre Lista::Lista(): m_inicio = nullptr
    std::cout << "Lista creada (vacia)" << '\n';
    return 0;
}
