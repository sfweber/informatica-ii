/* ej03_crear_lista · nodo.h — crearLista: cada valor ingresado crea un nodo al comienzo */
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
