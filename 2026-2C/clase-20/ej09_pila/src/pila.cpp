/* ej09_pila · pila.cpp — push/pop sin controlar llena/vacia */
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
    m_top++;
    m_datoPila[m_top] = dato;
}

int Pila::pop (void)
{
    int dato = m_datoPila[m_top];
    m_top--;
    return dato;
}
