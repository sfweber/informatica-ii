/* ej09_pila · pila.h — pila sobre un vector en el heap */
#ifndef PILA_H
#define PILA_H

class Pila
{
private:
    int  m_tamMax;
    int  m_top;
    int* m_datoPila;
public:
    Pila (int);
    ~Pila ();
    void push (int);
    int  pop (void);
    int  getTop (void);
    bool isEmpty (void);
    bool isFull (void);
};

#endif // PILA_H
