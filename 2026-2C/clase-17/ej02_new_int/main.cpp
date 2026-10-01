#include <iostream>

int main ()
{
    int *ptr {new int};          // reserva un int en el heap, sin inicializar

    *ptr = 10;

    std::cout << "ptr: " << ptr << "\t*ptr: " << *ptr << '\n';

    delete ptr;
    return 0;
}
