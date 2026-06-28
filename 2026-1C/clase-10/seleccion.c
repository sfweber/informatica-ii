/* Ordenamiento por selección */

#include <stdio.h>

int main()
{
    int i, j, iMenor ;
    int aux ;
    int vec[] = { 8 , 4 ,5 , 9 , 1 };
    int length = sizeof (vec) / sizeof(vec[0]);

    for ( i = 0 ; i < length - 1 ; i++ )
    {
        iMenor = i ;
        for (j=i+1 ; j < length  ; j++)
            if (vec[j]<vec[iMenor])
                iMenor = j ;

        if (i != iMenor)
        {
            aux      = vec[i] ;
            vec[i]   = vec[iMenor];
            vec[iMenor] = aux ;
        }

    }
    for (i=0; i< length ; i++)
        printf("%d\n", vec[i]);
    return 0;
}
