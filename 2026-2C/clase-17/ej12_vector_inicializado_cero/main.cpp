#include <iostream>

int main ()
{
    int  x {0};
    int *ptr {nullptr};

    std::cout << "Ingrese la cantidad de elementos: \n";
    std::cin >> x;

    if (x <= 0)
        return 0;

    ptr = new int[x] {};         // todos en cero

    for (int i = 0; i < x; i++)
        std::cout << *(ptr + i) << '\t';
    std::cout << '\n';

    delete[] ptr;
    return 0;
}
