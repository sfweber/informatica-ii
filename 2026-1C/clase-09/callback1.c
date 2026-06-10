/*Hacemos un programa que elija entre dos enteros, la condicion de la eleccion
 * se hace en tiempo de ejecucion*/

#include <stdio.h>

int max (int, int);
int min (int, int);
int aplicar (int (*) (int, int), int, int);

int main(void)
{
    int x = 10, y = 20, aux;
    aux = aplicar (max, x, y);
    printf ("Luego de aplicar max el resultado es %d\n", aux);
    aux = aplicar (min, x, y);
    printf ("Luego de aplicar min el resultado es %d\n", aux);

    return 0;
}

int max (int a, int b)
{
    return (a>b) ? a : b;
}

int min (int a, int b)
{
    return (a<b) ? a : b;
}

int aplicar (int (*cmp) (int, int), int x, int y)
{
    return cmp (x, y);

}
