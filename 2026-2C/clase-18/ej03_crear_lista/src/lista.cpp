/* ej03_crear_lista · lista.cpp — crearLista: cada valor ingresado crea un nodo al comienzo */
#include <iostream>
#include "lista.h"
#include "nodo.h"

Lista::Lista ()
{
    m_inicio = nullptr;
}

void Lista::crearLista ()
{
    int x {};
    m_inicio = nullptr;                // potencial memory leak: si ya habia nodos, se pierden
    std::cout << "El ingreso termina con -1" << '\n';
    do {
        std::cin >> x;
        if (x != -1)
            m_inicio = new Nodo (x, m_inicio);
    } while (x != -1);
}
