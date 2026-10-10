/* ej07_insertar_ultimo · nodo.h — getUltimo (nullptr si vacia) + insertarUltimo (delega en insertarPrimero si vacia) */
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
    void setSig (Nodo*);
};

#endif // NODO_H
