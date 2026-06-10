#include <stdio.h>

struct Figura {
    double dimension1;
    double dimension2;
    double (*area) (struct Figura*);
};

double area_rectangulo (struct Figura*);
double area_circulo (struct Figura*);

int main(void) {

    struct Figura rectangulo;
    rectangulo.dimension1 = 4.0;
    rectangulo.dimension2 = 5.0;
    rectangulo.area = area_rectangulo ;

    struct Figura circulo;
    circulo.dimension1 = 3.0;
    circulo.area = area_circulo;

    //usamos los punteros a funcion como si fueran metodos
    printf ("El area del rectangulo es %.2f\n", rectangulo.area(&rectangulo));
    printf ("El area del circulo es %.2f\n", circulo.area(&circulo));



    return 0;
}


double area_rectangulo (struct Figura* rec)
{
    double base = rec->dimension1;
    double altura = rec->dimension2;

    return base*altura;
}

double area_circulo (struct Figura* cir)
{
    double radio = cir->dimension1;
    return 3.1415 * radio * radio;
}
