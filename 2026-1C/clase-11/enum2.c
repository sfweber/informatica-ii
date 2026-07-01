/* TIPO: demo de enum (valores enteros) -- NO es una FSM (es prerequisito de la clase) */
#include <stdio.h>

// Definición de una enumeración para los días de la semana
enum DiaSemana{
    lunes, //el literal "lunes" es una constante int de valor cero
    martes, //el literal "martes" es una constante int de valor uno
    miercoles,
    jueves,
    viernes,
    sabado,
    domingo,
} ;


// Función principal
int main(void) {
    enum DiaSemana dia = miercoles;  // Asignar un día de la semana
    int j=jueves;
    printf ("%d\t%d\t%d\t%d", lunes, martes, miercoles,j);

    getchar();

    return 0;
}
