#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inicializar (int[], int);
void intercambiar(int*, int*);
void burbuja(int[], int );
void seleccion (int[] , int);
void quicksort(int[], int, int);

int main() {
    int n = 20000; // Tamaño del vector
    int vec1[n];
    clock_t inicio, fin;
    double tiempo_burbuja, tiempo_quicksort, tiempo_seleccion;

    // Inicializar los vectores con números aleatorios
    inicializar(vec1,n);

    // Medir el tiempo de burbuja
    inicio = clock();
    burbuja(vec1, n);
    fin = clock();
    tiempo_burbuja = ((double)(fin - inicio)) / CLOCKS_PER_SEC;


    // Inicializar los vectores con números aleatorios
    inicializar(vec1,n);
    // Medir el tiempo de selección
    inicio = clock();
    seleccion (vec1, n);
    fin = clock();
    tiempo_seleccion = ((double)(fin - inicio)) / CLOCKS_PER_SEC;


    // Inicializar los vectores con números aleatorios
    inicializar(vec1,n);
    // Medir el tiempo de Quicksort
    inicio = clock();
    quicksort(vec1, 0, n - 1);
    fin = clock();
    tiempo_quicksort = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

    printf("Tiempo de Burbuja: %lf segundos\n", tiempo_burbuja);
    printf("Tiempo de Seleccion: %lf segundos\n", tiempo_seleccion);
    printf("Tiempo de Quicksort: %lf segundos\n", tiempo_quicksort);

    return 0;
}

void inicializar (int vec[], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        vec[i] = rand();
    }
}

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
