#include <iostream>

int main ()
{
    int  x {0};
    int *ptr {nullptr};

    std::cout << "Ingrese la cantidad de elementos: \n";
    std::cin >> x;

    if (x <= 0)
        return 0;

    ptr = new int[x];            // observar la ubicacion del []

    for (int i = 0; i < x; i++)
        std::cout << *(ptr + i) << '\t';    // sin inicializar: no hay garantia de lo que sale
    std::cout << '\n';

    delete[] ptr;                // new[] se libera con delete[]
    return 0;
}
