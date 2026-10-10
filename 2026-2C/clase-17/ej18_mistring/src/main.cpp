#include <iostream>
#include "miString.h"

int main ()
{
    miString obj1 ("hola mundo");
    obj1.imprimir ();
    std::cout << "La primer letra del string es: ";
    std::cout << obj1.getCaracter (0) << "\n";
    obj1.cargar ("Este es el segundo");
    obj1.imprimir ();
    std::cout << "el largo es : " << obj1.getLargo () << "\n";
    obj1.agregar (", termina aca");
    obj1.imprimir ();

    // el objeto entero en el heap
    miString *pStr = new miString ("Vivo en el heap");   // new llama al constructor
    pStr -> imprimir ();                                  // -> : un metodo a traves del puntero
    std::cout << "el largo es : " << pStr -> getLargo () << "\n";
    delete pStr ;                                         // delete llama al destructor

    std::cout << "este es el fin del main" << "\n";
    return 0 ;
}
