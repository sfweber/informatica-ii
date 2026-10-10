/* ej05_destructor · lista.h — ~Lista libera todos los nodos */
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
};

#endif // LISTA_H
