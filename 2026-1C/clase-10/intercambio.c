/* Ordenamiento por intercambio */

#include <stdio.h>

int main()
{
    int i, j ;
    int aux ;
    int vec[] = { 8 , 4 ,5 , 9 , 1 };
    int length = sizeof (vec) / sizeof(vec[0]);

    for ( i = 0 ; i < length - 1 ; i++ )
        for (j=i+1 ; j < length  ; j++)
            if (vec[i]>vec[j])
            {
                aux      = vec[i] ;
                vec[i]   = vec[j];
                vec[j]   = aux ;
            }

    for (i=0; i< length ; i++)
        printf("%d\n", vec[i]);
    return 0;
}
