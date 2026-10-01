#include <iostream>

void triplicar (int *, int);

int main ()
{
    int vShort[] {1, 2, 3, 4, 5};
    int size = sizeof (vShort) / sizeof (vShort[0]);

    triplicar (vShort, size);    // paso del vector por direccion

    for (int i = 0; i < size; i++)
        std::cout << *(vShort + i) << '\t';
    std::cout << '\n';
    return 0;
}

void triplicar (int *vec, int size)
{
    // sizeof (vec) aca es el tamanio de un PUNTERO, no del vector
    for (int i = 0; i < size; i++)
        *(vec + i) *= 3;
}
