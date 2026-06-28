/* qsort con enteros - ascendente y descendente */
#include <stdio.h>
#include <stdlib.h>

/* Comparacion ascendente.
   Devuelve negativo si a va antes, positivo si a va despues, cero si iguales.
   Se usa (x > y) - (x < y) en vez de x - y para evitar overflow. */
int comparar_asc(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

/* Comparacion descendente: misma idea pero invertida. */
int comparar_desc(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x < y) - (x > y);
}

int main()
{
    int vec[] = { 8, 4, 5, 9, 1, 3, 7, 2 };
    int length = sizeof(vec) / sizeof(vec[0]);
    int i;

    /* Ordeno de menor a mayor */
    qsort(vec, length, sizeof(int), comparar_asc);

    printf("Ascendente:\n");
    for (i = 0; i < length; i++)
        printf("%d ", vec[i]);
    printf("\n\n");

    /* Ordeno de mayor a menor */
    qsort(vec, length, sizeof(int), comparar_desc);

    printf("Descendente:\n");
    for (i = 0; i < length; i++)
        printf("%d ", vec[i]);
    printf("\n");

    return 0;
}