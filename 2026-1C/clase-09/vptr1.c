#include <stdio.h>

int suma (int , int );
int resta (int , int );
int producto (int , int );
int division (int , int );
int resto (int , int );


int main(void)
{
    int (*vPtr [])(int, int) = {&suma, &resta, &producto, &division, &resto} ;

    int x, y, sel;
    x=30;
    y=2;

    printf ("\n\tIngrese una opcion");
    printf ("\n\t0. suma \n\t1. resta \n\t2. producto \n\t3. division \n\t4. resto\n\t");
    scanf ("%d", &sel);

    printf ("\n\tRESULTADO = %d", vPtr[sel](x,y));

    getchar();
    printf ("\n\n");
    getchar();
    return 0;
}


int suma (int x , int y )
{
    return x+y;
}
int resta (int x , int y )
{
    return x-y;
}
int producto (int x , int y )
{
    return x*y;
}
int division (int x , int y )
{
    return x/y;
}
int resto (int x , int y  )
{
    return x%y;
}
