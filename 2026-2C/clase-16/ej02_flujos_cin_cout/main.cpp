#include <iostream>


int main()
{
    int   i;
    float f;
    char  str[20];

    std::cout << "Ingrese un entero: " ;
    std::cin >> i ;

    std::cout << "Ingrese un flotante: " ;
    std::cin >> f ;

    std::cout << "Ingrese un string: " ;
    std::cin >> str ;

    std::cout << "Los valores ingresados son " << '\n' ;
    std::cout << "El entero: "   <<  i  << '\n';
    std::cout << "El flotante: " <<  f  << '\n';
    std::cout << "El string  : " << str << '\n';

    return 0;
}
