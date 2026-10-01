#include <iostream>

// Slide 4 (oculta). En Linux la pila es de 8 MB: con 1.000.000 de int (4 MB)
// el programa NO crashea. Con 3.000.000 (12 MB) sí. Hay que usar el vector,
// si no el compilador lo elimina.
int main ()
{
    int vec[3000000];

    vec[0] = 1;
    std::cout << "UTN FRH - INFO II " << vec[0] << '\n';
    return 0;
}
