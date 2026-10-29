/* ej11_cola_circular · circqueue.cpp — enqueue/dequeue con % y count */
#include <iostream>
#include "circqueue.h"

CircQueue::CircQueue (int size)
{
    m_tamMax = size;
    m_datoCola = new int [size];
    m_front = 0;
    m_rear = -1;
    m_count = 0;                       // cola vacia
}

CircQueue::~CircQueue ()
{
    delete [] m_datoCola;
}

void CircQueue::enqueue (int dato)
{
    if (isFull ())
    {
        std::cerr << "Error: la cola esta llena. El " << dato << " no se ingreso" << '\n';
        return;
    }
    m_rear = (m_rear + 1) % m_tamMax;  // el % es lo que la hace circular
    m_datoCola[m_rear] = dato;
    m_count++;
}

int CircQueue::dequeue (void)
{
    if (isEmpty ())
    {
        std::cerr << "Error: la cola esta vacia. No se puede leer" << '\n';
        return -1;
    }
    int dato = m_datoCola[m_front];
    if (m_front == m_rear)             // era el unico elemento: volvemos a la condicion inicial
    {
        m_front = 0;
        m_rear = -1;
    }
    else
        m_front = (m_front + 1) % m_tamMax;
    m_count--;
    return dato;
}

int CircQueue::getFront (void)
{
    return m_datoCola[m_front];
}

bool CircQueue::isEmpty (void)
{
    return m_count == 0;
}

bool CircQueue::isFull (void)
{
    return m_count == m_tamMax;
}

int CircQueue::getSize (void)
{
    return m_tamMax;
}
