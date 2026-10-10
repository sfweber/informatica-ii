/* ej04_recorrer · nodo.h — recorrerLista con los getters de Nodo */
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
    Nodo* getSig ();
    int getDato ();
};

#endif // NODO_H
