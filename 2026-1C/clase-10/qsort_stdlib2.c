/* qsort con estructuras - ordenar por un campo */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nombre[50];
    int edad;
} Persona;

/* Ordena por edad (ascendente).
   El void * apunta directamente a una Persona, asi que se castea
   a (const Persona *) y se accede al campo con ->. */
int comparar_edad(const void *a, const void *b)
{
    const Persona *p1 = (const Persona *)a;
    const Persona *p2 = (const Persona *)b;
    return (p1->edad > p2->edad) - (p1->edad < p2->edad);
}

int main()
{
    Persona personas[] = {
        { "Ana",     30 },
        { "Beto",    22 },
        { "Carlos",  45 },
        { "Diana",   22 },
        { "Esteban", 38 }
    };
    int length = sizeof(personas) / sizeof(personas[0]);
    int i;

    qsort(personas, length, sizeof(Persona), comparar_edad);

    printf("Personas ordenadas por edad:\n");
    for (i = 0; i < length; i++)
        printf("%-10s %d\n", personas[i].nombre, personas[i].edad);

    return 0;
}