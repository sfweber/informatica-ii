/* Quick Sort*/
#include <stdio.h>

void quicksort(int[], int , int );

int main()
{
    int i;
    int vec[] = { 5 , 9 , 1 , 8 , 3 , 7 , 6 , 4 };

    int length = sizeof (vec) / sizeof(vec[0]);

    quicksort(vec , 0, (length-1));

    for (i=0; i< length ; i++)
        printf("%d\n", vec[i]);

    return 0;
}



void quicksort(int vec[], int inicio, int fin)
{
    int i, j, central;
    int pivote;
    int aux;
    central = (inicio + fin) / 2;
    pivote = vec[central];
    i = inicio;
    j = fin;
    do {
        while (vec[i] < pivote) i++;
        while (vec[j] > pivote) j--;
        if (i <= j)
        {
            aux  = vec[i] ;
            vec[i] = vec[j];
            vec[j] = aux ;

            i++;
            j--;
        }
    }while (i <= j);
    if (inicio < j)
        quicksort(vec, inicio, j); // mismo proceso con sublista izqda
    if (i < fin)
        quicksort(vec, i, fin); // mismo proceso con sublista drcha

}
