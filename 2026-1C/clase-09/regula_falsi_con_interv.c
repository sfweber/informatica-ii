#include <stdio.h>
#include <math.h>

float funcion (float);
float rf (float (*)(float), float , float , float );
void buscar_intervalo(float (*)(float), float , float , float , float* , float*);

int main()
{
    float a, b, error = 0.1;
    float inicio = -50.0;
    float fin = 50.0;
    float paso = 10;


    buscar_intervalo(&funcion, inicio, fin, paso, &a, &b);

    if (isnan(a) || isnan(b)) {
        printf("\nNo se encontro un cambio de signo en el rango especificado.\n");
    } else {
        printf("\nEl intervalo donde la funcion cambia de signo es: [%f, %f]\n", a, b);
    }


    printf ("\n\n El cruce por cero se encuentra en %.2f", rf (funcion, a , b , error)) ;

    printf ("\n\n");
    getchar();

    return 0;
}

float funcion (float x)
{
    return x*x*x-10*x*x+31*x-40;
}

void buscar_intervalo(float (*func)(float), float inicio, float fin, float paso, float *a, float *b) {
    float x = inicio;
    while (x < fin) 
    {
        if (func(x) * func(x + paso) < 0) 
        {
            *a = x;
            *b = x + paso;
            return;
        }
        x += paso;
    }
    // Si no se encuentra intervalo, setear a y b a NaN
    *a = NAN;
    *b = NAN;
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

