#include <stdio.h>
#include <math.h>

double funcion (double);
double rf (double (*)(double), double , double , double , int );

int main()
{
    double a, b, error;
    int maxIter;
    a = 0.0 ;
    b = 7.0 ;
    error = 0.1 ;
    maxIter = 100;

    double resultado = rf (funcion, a , b , error, maxIter) ;
    if ( !isnan( (resultado) ))
        printf ("\n\n El cruce por cero se encuentra en %.2f", resultado) ;
    else
        printf ("\n\n No se encontro resultado");


    printf ("\n\n");
    getchar();

    return 0;
}

double funcion (double x)
{
    return x*x*x-10*x*x+31*x-40;
}

double rf (double (*pf)(double), double a , double b , double error, int maxIter)
{
    double fa = pf(a);
    double fb = pf(b);
    double x, fx;

    if (fa*fb > 0)
    {
        printf ("El intervalo no garantiza raiz.\n");
        return NAN;
    }

    int flagConvergencia = 0;

    for (int i=0; i<maxIter && !flagConvergencia; i++)
    {
        x = a - fa*(b-a)/(fb-fa);
        fx = pf(x);
        printf ("\n %10.2f %10.2f", x, pf(x));
        getchar();

        if (fabs(fx) < error)
            flagConvergencia = 1;
        else if (fa * fx < 0)
        {
            a = x;
            fa = fx;
        }
        else
        {
            b = x;
            fb = fx;
        }

    }

    if (!flagConvergencia)
    {
        printf ("No se convergio a un resultado despues de %d", maxIter);
        return NAN;
    }

    return x;
}
