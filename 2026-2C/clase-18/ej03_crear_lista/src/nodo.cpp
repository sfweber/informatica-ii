/* ej03_crear_lista · nodo.cpp — crearLista: cada valor ingresado crea un nodo al comienzo */
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
