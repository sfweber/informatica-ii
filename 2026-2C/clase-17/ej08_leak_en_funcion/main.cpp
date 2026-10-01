#include <iostream>

void asignar (int);

int main ()
{
    int x;
    std::cout << "Ingrese un valor: ";
    std::cin >> x;
    asignar (x);
    return 0;
}

void asignar (int aX)
{
    int *ptr {new int {aX}};
    std::cout << "Valor asignado en el heap: " << *ptr << '\n';
}                                // ptr muere aca: ya no hay forma de hacer delete -> memory leak
