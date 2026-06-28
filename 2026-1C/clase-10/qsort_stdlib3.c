/* qsort con cadenas (arreglo de char *) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* OJO: cada elemento del arreglo es un char *, asi que el void *
   apunta a un char *. Por eso se castea a (const char **) y se
   desreferencia una vez para obtener el char * real.
   strcmp ya devuelve negativo / cero / positivo, justo lo que qsort espera. */
int comparar_str(const void *a, const void *b)
{
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}

int main()
{
    const char *nombres[] = { "Carlos", "Ana", "Beto", "Diana", "Esteban" };
    int length = sizeof(nombres) / sizeof(nombres[0]);
    int i;

    qsort(nombres, length, sizeof(char *), comparar_str);

    printf("Nombres ordenados alfabeticamente:\n");
    for (i = 0; i < length; i++)
        printf("%s\n", nombres[i]);

    return 0;
}