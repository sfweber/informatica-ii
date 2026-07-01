/* Ejemplo 2 — detector de la secuencia "abcd".  TIPO: Mealy
 * Ingresada por teclado, con maquina de estados
 * (version basica con switch-case). Cualquier caracter fuera de la secuencia
 * esperada vuelve la maquina al estado inicial.
 *
 * Se lee un caracter por vuelta y se ignora el '\n', que
 * no pertenece al alfabeto del problema.
 */
#include <stdio.h>

typedef enum {
    estado_A,
    estado_B,
    estado_C,
    estado_D
} States;

int main(void)
{
    States NextState;
    int c;

    NextState = estado_A;          /* estado inicial: en una FSM siempre se define uno */

    c = getchar();
    while (c != EOF) {
        if (c != '\n') {           /* ignora el Enter */
            switch (NextState) {
            case estado_A:
                /* solo avanza si llega la 'a' */
                if (c == 'a')
                    NextState = estado_B;
                else
                    printf("- caracter esperado: a. Permanece en el estado inicial\n");
                break;
            case estado_B:
                if (c == 'b')
                    NextState = estado_C;
                else {
                    printf("- caracter esperado: b. Ingresado: %c. Vuelve al inicio\n", c);
                    NextState = estado_A;
                }
                break;
            case estado_C:
                if (c == 'c')
                    NextState = estado_D;
                else {
                    printf("- caracter esperado: c. Ingresado: %c. Vuelve al inicio\n", c);
                    NextState = estado_A;
                }
                break;
            case estado_D:
                if (c != 'd')
                    printf("- caracter esperado: d. Ingresado: %c. Vuelve al inicio\n", c);
                else
                    printf(" OK -> Secuencia aceptada\n");
                NextState = estado_A;
                break;
            }
        }
        c = getchar();
    }
    return 0;
}
