#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float funcion (float);
float rf (float (*)(float), float , float , float );

int main()
{
    float a, b, error;
    a = 0.0 ;
    b = 7.0 ;
    error = 0.1 ;
    printf ("\n\n El cruce por cero se encuentra en %.2f", rf (funcion, a , b , error)) ;

    printf ("\n\n");
    getchar();

    return 0;
}

float funcion (float x)
{
    return x*x*x-10*x*x+31*x-40;
}

float rf (float (*pf)(float), float a , float b , float error)
{
    float x;

    x = a - pf(a)*(b-a)/(pf(b)-pf(a));

    printf ("\n %10.2f %10.2f", x, pf(x));
    getchar();
    if ( fabs(pf(x)) < error)
        return x;
    if (pf(x)*pf(a)>0)
        a = x ;
    else
        b = x ;

    return rf(pf, a, b, error);

}
