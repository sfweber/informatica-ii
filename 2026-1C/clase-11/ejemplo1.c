/* Ejemplo 1 — contador par/impar.  TIPO: Moore (la salida PAR/IMPAR depende SOLO del estado)
 *
 * Realizar un programa que permita ingresar por teclado cualquier secuencia de
 * 0 y 1. En pantalla se debe mostrar si la cantidad de 1 ingresados es PAR o
 * IMPAR. Utilizar maquinas de estado finito.
 *
 * Maquina de MOORE: la salida (PAR / IMPAR) depende SOLO del estado.
 * Se lee un caracter por vuelta arriba del switch y se ignora cualquiera que no
 * sea '0' o '1'.
 */
#include <stdio.h>

typedef enum {
    PAR,
    IMPAR
} Estado;

int main(void)
{
    Estado estado;
    int c;

    estado = PAR;                       /* 0 unos ingresados -> PAR */
    printf("La cantidad de 1 ingresados es PAR\n");

    c = getchar();

    /* Para terminar: Ctrl+D (Linux) o Ctrl+Z+Enter (Windows).
     O pipear la entrada:  echo "101" | ./ejemplo1   */
    while (c != EOF) {
        if (c == '0' || c == '1') {     /* solo '0' y '1' son entradas validas */
            switch (estado) {           /* break de switch = excepcion aceptada */
            case PAR:
                if (c == '1')
                    estado = IMPAR;
                break;
            case IMPAR:
                if (c == '1')
                    estado = PAR;
                break;
            }
            /* salida de Moore: depende solo del estado alcanzado */
            if (estado == PAR)
                printf("La cantidad de 1 ingresados es PAR\n");
            else
                printf("La cantidad de 1 ingresados es IMPAR\n");
        }
        c = getchar();
    }
    return 0;
}
