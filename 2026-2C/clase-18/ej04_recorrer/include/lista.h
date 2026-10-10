/* ej04_recorrer · lista.h — recorrerLista con los getters de Nodo */
#ifndef LISTA_H
#define LISTA_H
#include "nodo.h"

class Lista
{
private:
    Nodo* m_inicio;
public:
    Lista ();
    void crearLista ();
    void recorrerLista ();
};

#endif // LISTA_H
