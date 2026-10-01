#include <iostream>

int main ()
{
    int  i {0};
    int *ptr {new int {0}};

    ptr = &i;                    // el bloque del heap queda sin nadie que lo apunte -> leak
                                 // (y un "delete ptr" ahora liberaria memoria de la PILA)
    std::cout << "*ptr: " << *ptr << '\n';
    return 0;
}
