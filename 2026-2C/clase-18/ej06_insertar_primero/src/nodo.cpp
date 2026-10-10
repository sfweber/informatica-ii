/* ej06_insertar_primero · nodo.cpp — insertarPrimero en 3 pasos (con el setter setSig de Nodo) */
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
