#include <iostream>
#include <cstring>
#include "miString.h"

miString::miString (const char* str)
{
    m_largo = std::strlen (str);
    m_texto = new char [m_largo + 1];      // + 1: el lugar para el '\0'
    std::strcpy (m_texto, str);
}

miString::~miString ()
{
    delete [] m_texto ;
}

void miString::imprimir (void)
{
    std::cout << m_texto << "\n" ;
}

char miString::getCaracter (int pos)
{
    if (pos >= 0 && pos < m_largo)         // posiciones validas: 0 .. m_largo-1
        return m_texto[pos];
    else
    {
        std::cout << "pos no valido" << "\n";
        return '\0';
    }
}

void miString::cargar (const char* str)
{
    delete [] m_texto;                     // primero se libera el bloque viejo
    m_largo = std::strlen (str);
    m_texto = new char [m_largo + 1];
    std::strcpy (m_texto, str);
}

int miString::getLargo (void)
{
    return m_largo;
}

void miString::agregar (const char* str)
{
    int largoNuevo = m_largo + std::strlen (str);
    char* aux;

    aux = new char [largoNuevo + 1];       // bloque mas grande
    std::strcpy (aux, m_texto);            // lo viejo
    std::strcpy (aux + m_largo , str );    // lo nuevo, a continuacion

    m_largo = largoNuevo;
    delete [] m_texto;                     // se libera el viejo
    m_texto = aux ;
}
