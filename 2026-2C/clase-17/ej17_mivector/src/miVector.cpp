#include "miVector.h"
#include <iostream>
#include <cstdlib>

miVector::miVector (int tam)
{
    if (tam <= 0)
    {
        // un constructor no devuelve nada: no puede avisar que fallo.
        // exit() corta el programa aca mismo, SIN ejecutar los destructores
        // de los objetos locales que ya existian.
        std::cout << "El tamaño debe ser mayor que cero\n";
        std::exit (0);
    }

    n_tam = tam ;
    n_vector = new int [tam] {};     // todos en cero
}

miVector::~miVector ()
{
    delete[] n_vector ;
}

void miVector::setValor (int valor , int pos)
{
    if (pos >= 0 && pos < n_tam)     // posiciones validas: 0 .. n_tam-1
        n_vector[pos] = valor ;
    else
        std::cout << "los parametros ingresados no son validos\n" ;
}

int miVector::getValor (int pos)
{
    if (pos >= 0 && pos < n_tam)
        return n_vector[pos];
    else
    {
        std::cout << "los parametros ingresados no son validos\n" ;
        return 0;                    // ojo: no se distingue de un 0 guardado
    }
}

int miVector::getTam (void)
{
    return n_tam;
}
