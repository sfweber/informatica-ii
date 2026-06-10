#include <stdio.h>
#define NUM_FUNCS 5


int suma (int , int );
int resta (int , int );
int producto (int , int );
int division (int , int );
int resto (int , int );


int main(void)
{
    int (*vPtr [NUM_FUNCS])(int, int) = {&suma, &resta, &producto, &division, &resto} ;

    int x=6, y=2;

    for (int i = 0; i< NUM_FUNCS; i++)
    {
        printf ("La operacion %d entre %d y %d es %d\n",i, x, y, vPtr[i](x,y));
    }

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
