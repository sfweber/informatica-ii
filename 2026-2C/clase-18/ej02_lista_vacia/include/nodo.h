/* ej02_lista_vacia · nodo.h — class Lista con m_inicio = nullptr */
#ifndef NODO_H
#define NODO_H

class Nodo
{
private:
    int m_dato;
    Nodo* m_sig;
public:
    Nodo (int);
    Nodo (int, Nodo*);
};

#endif // NODO_H
