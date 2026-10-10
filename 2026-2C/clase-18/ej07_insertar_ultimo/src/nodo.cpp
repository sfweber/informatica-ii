/* ej07_insertar_ultimo · nodo.cpp — getUltimo (nullptr si vacia) + insertarUltimo (delega en insertarPrimero si vacia) */
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

void Nodo::setSig (Nodo* sig)
{
    m_sig = sig;
}
