/* ej07_insertar_ultimo · lista.cpp — getUltimo (nullptr si vacia) + insertarUltimo (delega en insertarPrimero si vacia) */
#include <iostream>
#include "lista.h"
#include "nodo.h"

Lista::Lista ()
{
    m_inicio = nullptr;
}

Lista::~Lista ()
{
    Nodo* p = m_inicio;
    while (p != nullptr)
    {
        Nodo* sig = p->getSig ();
        delete p;
        p = sig;
    }
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

void Lista::recorrerLista ()
{
    std::cout << "Recorriendo lista: " << '\n';
    for (Nodo* p = m_inicio ; p != nullptr ; p = p->getSig ())
        std::cout << p->getDato () << '\n';
}

void Lista::insertarPrimero (int dato)
{
    //paso 1: crear el nodo
    Nodo* nuevo = new Nodo (dato);
    //paso 2: el nuevo apunta al que era el primero
    nuevo->setSig (m_inicio);
    //paso 3: el nuevo pasa a ser el primero
    m_inicio = nuevo;
}

Nodo* Lista::getUltimo ()
{
    Nodo* p = m_inicio;
    if (p == nullptr)                  // lista vacia: no hay ultimo
        return nullptr;
    while (p->getSig () != nullptr)
        p = p->getSig ();
    return p;
}

void Lista::insertarUltimo (int dato)
{
    if (m_inicio == nullptr)           // lista vacia: el ultimo es tambien el primero
    {
        insertarPrimero (dato);
        return;
    }
    //paso 1: crear el nodo (apunta a nullptr: va a ser el ultimo)
    Nodo* nuevo = new Nodo (dato);
    //paso 2: buscar el ultimo y engancharle el nuevo
    Nodo* ultimo = getUltimo ();
    ultimo->setSig (nuevo);
}
