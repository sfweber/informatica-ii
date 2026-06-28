#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void burbuja(int vec[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (vec[j] > vec[j+1]) {
                intercambiar(&vec[j], &vec[j+1]);
            }
        }
    }
}


void seleccion (int vec[] , int n)
{
    int i, j, iMenor ;
    int aux ;


    for ( i = 0 ; i < n - 1 ; i++ )
    {
        iMenor = i ;
        for (j=i+1 ; j < n  ; j++)
            if (vec[j]<vec[iMenor])
                iMenor = j ;

        if (i != iMenor)
        {
            aux      = vec[i] ;
            vec[i]   = vec[iMenor];
            vec[iMenor] = aux ;
        }

    }

}



void quicksort(int vec[], int inicio, int fin) {
    int i, j, central;
    int pivote;

    central = (inicio + fin) / 2;
    pivote = vec[central];
    i = inicio;
    j = fin;
    do {
        while (vec[i] < pivote) i++;
        while (vec[j] > pivote) j--;
        if (i <= j)
        {
            intercambiar(&vec[j], &vec[i]);

            i++;
            j--;
        }
    }while (i <= j);
    if (inicio < j)
        quicksort(vec, inicio, j); // mismo proceso con sublista izqda
    if (i < fin)
        quicksort(vec, i, fin); // mismo proceso con sublista drcha
}

/* comparador para qsort de la libreria estandar (unidad 5: punteros a funcion).
   Devuelve <0 si a va antes, 0 si son iguales, >0 si a va despues.
   La forma (x>y)-(x<y) es segura: no desborda como x-y. */
int comparar(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main() {
    int n = 20000000; // Tamaño del vector. Para que se note la diferencia
                   // entre quicksort y qsort, subir a ~2000000.
    int *original = malloc(n * sizeof(int));
    int *vec      = malloc(n * sizeof(int));   // copia de trabajo, fresca para cada algoritmo
    if (!original || !vec) {
        fprintf(stderr, "No se pudo reservar memoria para n = %d\n", n);
        return 1;
    }

    // Vector base con numeros aleatorios; cada algoritmo ordena una copia identica
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        original[i] = rand();

    clock_t inicio, fin;
    double tiempo_burbuja, tiempo_seleccion, tiempo_quicksort, tiempo_qsort;

  /*  // Burbuja
    for (int i = 0; i < n; i++) vec[i] = original[i];
    inicio = clock();
    burbuja(vec, n);
    fin = clock();
    tiempo_burbuja = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

    // Seleccion
    for (int i = 0; i < n; i++) vec[i] = original[i];
    inicio = clock();
    seleccion(vec, n);
    fin = clock();
    tiempo_seleccion = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
*/
    // Quicksort (el que codeamos)
    for (int i = 0; i < n; i++) vec[i] = original[i];
    inicio = clock();
    quicksort(vec, 0, n - 1);
    fin = clock();
    tiempo_quicksort = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

    // qsort de la libreria estandar
    for (int i = 0; i < n; i++) vec[i] = original[i];
    inicio = clock();
    qsort(vec, n, sizeof(int), comparar);
    fin = clock();
    tiempo_qsort = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

    printf("n = %d\n", n);
  //  printf("Tiempo de Burbuja:        %lf segundos\n", tiempo_burbuja);
   // printf("Tiempo de Seleccion:      %lf segundos\n", tiempo_seleccion);
    printf("Tiempo de Quicksort:      %lf segundos\n", tiempo_quicksort);
    printf("Tiempo de qsort (stdlib): %lf segundos\n", tiempo_qsort);

    free(original);
    free(vec);
    return 0;
}
