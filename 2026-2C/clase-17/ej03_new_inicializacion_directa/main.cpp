#include <iostream>

int main ()
{
    int *ptr {new int (5)};      // inicializacion directa

    std::cout << "ptr: " << ptr << "\t*ptr: " << *ptr << '\n';

    delete ptr;
    return 0;
}
