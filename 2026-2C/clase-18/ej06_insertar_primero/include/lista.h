/* ej06_insertar_primero · lista.h — insertarPrimero en 3 pasos (con el setter setSig de Nodo) */
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
};

#endif // LISTA_H
