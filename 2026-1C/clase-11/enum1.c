/* TIPO: demo de enum + switch -- NO es una FSM (es prerequisito de la clase) */
#include <stdio.h>

// Definición de una enumeración para los días de la semana
enum DiaSemana{
    // Estos son los enumeradores
    // Son constantes simbólicas que definen todos los valores posibles que este tipo puede contener
    // Cada enumerador está separado por una coma, no un punto y coma
    lunes,
    martes,
    miercoles,
    jueves,
    viernes,
    sabado,
    domingo,  // última coma opcional
} ; // la definición enum debe finalizar con un punto y coma


// Función principal
int main(void) {
    enum DiaSemana dia = miercoles;  // Asignar un día de la semana

    // Imprimir un mensaje basado en el día de la semana
    switch (dia) {
        case lunes:
            printf("Hoy es lunes. Comienza la semana!\n");
            break;
        case martes:
            printf("Hoy es martes. Segundo dia de la semana.\n");
            break;
        case miercoles:
            printf("Hoy es miercoles. Mitad de semana.\n");
            break;
        case jueves:
            printf("Hoy es jueves. Casi el fin de semana.\n");
            break;
        case viernes:
            printf("Hoy es viernes. Ultimo dia de trabajo.\n");
            break;
        case sabado:
            printf("Hoy es sabado. Dia de descanso.\n");
            break;
        case domingo:
            printf("Hoy es domingo. No puede ser.\n");
            break;
        default:
            printf("Día inválido.\n");
            break;
    }

    getchar();

    return 0;
}
