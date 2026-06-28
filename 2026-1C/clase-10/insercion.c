/* Ordenamiento por insercion*/

#include <stdio.h>

int main()
{
    int i, j ;
    int aux ;
    int vec[] = { 18 , 42 ,39 , 40 , 3 };
    int length = sizeof (vec) / sizeof(vec[0]);

    for ( i = 1 ; i < length ; i++ )
    {
        j = i ;
        aux = vec[i];

        while (j > 0 && aux < vec [j-1])
        {
            vec[j] = vec [j-1];
            j--;
        }
        vec[j]=aux;
    }

    for (i=0; i< length ; i++)
        printf("%d\n", vec[i]);
    return 0;
}
