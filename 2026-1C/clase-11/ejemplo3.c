/* Ejemplo 3 — el detector "abcd" (Ejemplo 2) EXTENDIDO con una variable.  TIPO: EFSM
 *
 * La maquina es la MISMA del Ejemplo 2 (4 estados A->B->C->D que detectan "abcd").
 * Lo nuevo: contamos CUANTAS veces aparecio la secuencia. Ese conteo no se puede
 * meter en los estados (podria ser cualquier numero) -> hace falta una VARIABLE.
 * FSM (varios estados) + variable de datos = EFSM (extended FSM).
 *
 * La accion sobre la variable (contador++) va en la TRANSICION que completa "abcd"
 * (estilo Mealy): ver la slide "¿donde van las variables en el diagrama?".
 *
 * Compilar: gcc -Wall -Wextra ejemplo3.c -o ejemplo3
 * Probar:   echo "abcdxabcd" | ./ejemplo3     (2 detecciones)
 */
#include <stdio.h>

typedef enum { estado_A, estado_B, estado_C, estado_D } Estado;

int main(void)
{
    Estado estado;
    int c;
    int contador;          /* la VARIABLE: cuantas veces aparecio "abcd" */

    estado = estado_A;
    contador = 0;

    c = getchar();
    while (c != EOF) {
        if (c != '\n') {
            switch (estado) {       /* break de switch = excepcion aceptada */
            case estado_A:
                estado = (c == 'a') ? estado_B : estado_A;
                break;
            case estado_B:
                if (c == 'b')      estado = estado_C;
                else               estado = (c == 'a') ? estado_B : estado_A;
                break;
            case estado_C:
                if (c == 'c')      estado = estado_D;
                else               estado = (c == 'a') ? estado_B : estado_A;
                break;
            case estado_D:
                if (c == 'd') {
                    contador++;                                    /* accion en la transicion */
                    printf("abcd detectado. Total: %d\n", contador);
                    estado = estado_A;
                } else {
                    estado = (c == 'a') ? estado_B : estado_A;
                }
                break;
            }
        }
        c = getchar();
    }
    return 0;
}
