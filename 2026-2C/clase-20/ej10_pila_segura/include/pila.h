/* ej10_pila_segura · pila.h — se agrega borrarPila */
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
    void borrarPila (void);
};

#endif // PILA_H
