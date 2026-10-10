/* ej05_destructor · nodo.cpp — ~Lista libera todos los nodos */
#include "nodo.h"

Nodo::Nodo (int dato)
{
    m_dato = dato;
    m_sig = nullptr;
}

Nodo::Nodo (int dato, Nodo* sig)
{
    m_dato = dato;
    m_sig = sig;
}

Nodo* Nodo::getSig ()
{
    return m_sig;
}

int Nodo::getDato ()
{
    return m_dato;
}
