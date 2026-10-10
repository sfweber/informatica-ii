/* ej03_crear_lista · lista.h — crearLista: cada valor ingresado crea un nodo al comienzo */
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
};

#endif // LISTA_H
