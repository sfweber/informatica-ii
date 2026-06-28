/* Shell Sort - version insercion */
#include <stdio.h>

int main()
{
    int i, j, aux, paso;
    int vec[] = { 3, 9, 1, 8, 5, 7, 6, 4 };
    int length = sizeof(vec) / sizeof(vec[0]);

    for (paso = length/2; paso > 0; paso = paso/2)
    {
        for (i = paso; i < length; i++)
        {
            aux = vec[i];
            j = i;
            while (j >= paso && vec[j-paso] > aux)
            {
                vec[j] = vec[j-paso];
                j -= paso;
            }
            vec[j] = aux;
        }
    }

    for (i = 0; i < length; i++)
        printf("%d\n", vec[i]);
    return 0;
}
