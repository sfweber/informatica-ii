#include <iostream>

int main ()
{
    int *ptr {new int {5}};
    std::cout << "ptr: " << ptr << "\t*ptr: " << *ptr << '\n';

    delete ptr;                  // la memoria vuelve al programa; ptr sigue apuntando ahi

    std::cout << "\nVamos otra vez:\n"
              << "ptr: " << ptr << "\t*ptr: " << *ptr << '\n';   // COMPORTAMIENTO INDEFINIDO
    return 0;
}
