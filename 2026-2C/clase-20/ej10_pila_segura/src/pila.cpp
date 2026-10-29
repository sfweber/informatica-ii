/* ej10_pila_segura · pila.cpp — push/pop controlan overflow/underflow */
#include <iostream>
#include "pila.h"

Pila::Pila (int tamMax)
{
    m_tamMax = tamMax;
    m_datoPila = new int [tamMax];     // el vector vive en el heap: el tamano se conoce en ejecucion
    m_top = -1;                        // pila vacia
}

Pila::~Pila ()
{
    delete [] m_datoPila;
}

int Pila::getTop (void)
{
    return m_datoPila[m_top];
}

bool Pila::isEmpty (void)
{
    return m_top == -1;
}

bool Pila::isFull (void)
{
    return m_top == (m_tamMax - 1);
}

void Pila::push (int dato)
{
    if (isFull ())
    {
        std::cerr << "Pila llena, no se pudo insertar el elemento " << dato << '\n';
        return;
    }
    m_top++;
    m_datoPila[m_top] = dato;
}

int Pila::pop (void)
{
    if (isEmpty ())
    {
        std::cerr << "Pila vacia, no se pueden extraer mas elementos" << '\n';
        return -1;
    }
    int dato = m_datoPila[m_top];
    m_top--;
    return dato;
}

void Pila::borrarPila (void)
{
    m_top = -1;                        // los datos quedan en el vector, pero ya no son parte de la pila
}
