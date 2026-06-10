#include <stdio.h>

int cuadrado (int);
int cubo (int);
int suma (int (*)(int), int  , int  );

int main(void)
{
    int (*vPtr [])(int) = {&cuadrado, &cubo} ;

    int x, y, sel;
    x=3;
    y=2;

    printf ("\n\tIngrese una opcion");
    printf ("\n\t0. suma de cuadrados \n\t1. suma de cubos \n\t");
    scanf ("%d", &sel);

    if (sel>=0 && sel<2)
        printf ("\n\tRESULTADO = %d", suma (vPtr[sel], x, y ));
    else
        printf ("\n\tSeleccion Incorrecta");
    getchar();
    printf ("\n\n");
    getchar();
    return 0;
}


int cuadrado (int x )
{
    return x*x;
}
int cubo (int x  )
{
    return x*x*x;
}

int suma (int (*pf)(int), int x , int y )
{
    return pf(x)+pf(y);
}
