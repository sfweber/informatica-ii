/* Ordenamiento por burbujeo*/

#include <stdio.h>

int main()
{
    int i, j ;
    int aux ;
    int vec[] = { 8 , 4 ,5 , 9 , 1 };
    int length = sizeof (vec) / sizeof(vec[0]);
    
    for ( i = 0 ; i < length - 1 ; i++ )
        for (j=0 ; j < length -i - 1 ; j++)
            if (vec[j]>vec[j+1])
            {
                aux      = vec[j] ;
                vec[j]   = vec[j+1];
                vec[j+1] = aux ;
            }
    
    for (i=0; i< length ; i++)
        printf("%d\n", vec[i]);
    return 0;
}
