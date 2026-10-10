/* ej07_insertar_ultimo · lista.h — getUltimo (nullptr si vacia) + insertarUltimo (delega en insertarPrimero si vacia) */
#ifndef LISTA_H
#define LISTA_H
#include "nodo.h"

class Lista
{
private:
    Nodo* m_inicio;
public:
    Lista ();
    ~Lista ();
    void crearLista ();
    void recorrerLista ();
    void insertarPrimero (int);
    Nodo* getUltimo ();
    void insertarUltimo (int);
};

#endif // LISTA_H
