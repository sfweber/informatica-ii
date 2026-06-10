#include <stdio.h>

int suma (int a, int b)
{
    return a + b ;
}

int opuesto (int a)
{
    return -a;
}

// Definicion del tipo de puntero a funcion que recibe dos int y devuelve int
typedef int (*opBinaria)(int, int);
// Definicion del tipo de puntero a funcion que recibe int y devuelve int
typedef int (*opUnaria) (int);

int main(void)
{
    opBinaria ejemploPtr1 = &suma;
    opUnaria ejemploPtr2 = &opuesto;

    int x, y, z;
    x=30;
    y=2*x;

    z = ejemploPtr1 (x,y);
    printf ("La suma es: %d\n", z);
    printf ("El opuesto es: %d\n", ejemploPtr2(z));

    getchar();
    return 0;
}
