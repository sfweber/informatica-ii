#include <iostream>
#include "miVector.h"

int main ()
{
    int tam {};
    std::cout << "Ingrese el tamano del vector: ";
    std::cin >> tam ;

    miVector obj1 (tam);
    miVector obj2 (-1);              // a proposito: el constructor hace exit(0) y el programa
                                     // termina ACA. Comentar esta linea para ver el resto.

    obj1.setValor (99 , 1);          // (valor, pos)
    std::cout << "tam = " << obj1.getTam () << std::endl ;
    std::cout << "obj[1] = " << obj1.getValor (1) << std::endl ;

    std::cout << "fin del main" << "\n" ;
    return 0 ;
}
