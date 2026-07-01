/* TIPO: EFSM (FSM extendida) -- usa variables (cantBuffer/indBuffer/chkBuffer) y las
 *       transiciones dependen de ellas, no solo del byte. No es Moore ni Mealy puro.
 *
 * Ejemplo 4 - Tratamiento de un protocolo de comunicaciones con maquina de estados.
 * Protocolo:  | STX | CANT_DATOS | DATOS | CHK | ETX |
 *   STX  (1 byte) -> inicio (0x02)
 *   CANT_DATOS (1 byte) -> cantidad de datos
 *   DATOS (N bytes) -> los datos
 *   CHK  (1 byte) -> checksum (XOR de todos los datos)
 *   ETX  (1 byte) -> fin (0x03)
 * Adaptado y traducido de https://sergioprado.org/maquina-de-estados-em-c/
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 512
#define STX 0x02
#define ETX 0x03

typedef enum {
    EST_STX = 0,
    EST_CANT,
    EST_DATOS,
    EST_CHK,
    EST_ETX
} Estados;

void mostrarPaquete (unsigned char *, int );
void recibir(unsigned char *, int );

int main (void) {
    unsigned char datos1[] = {STX, 8, 11, 22, 33, 44 , 55 ,66,77,88, 112, ETX };
    /***************************************************************************************************************
     *   unsigned char datos1[] = {STX, 8, 11, 22, 33, 44 , 55 ,66,77,88, 112, ETX };
     *   unsigned char datos1[] = {STX, 7, 11, 22, 33, 44 , 55 ,66,77, 40, ETX };
     *   unsigned char datos1[] = {STX, 6, 11, 22, 33, 44 , 55 ,66, 101, ETX };
     *       int A;
     *       A = 11 ^ 22 ^ 33 ^ 44 ^ 55 ^ 66   ;
     *        printf ("%d", A);
     ****************************************************************************************************************/

    recibir (datos1, sizeof (datos1));

    return 0;
}


void mostrarPaquete (unsigned char *datos, int cantidad){
    int i;
    printf ("Imprimiendo datos recibidos....\n");
    if (cantidad==0)
        printf ("---SIN DATOS---\n\n");
    else {
        for (i=0 ; i<cantidad; i++)
           printf ("Dato[%d]=%d\n", i, datos[i]);
        }

}

/* maquina de estados */
void recibir(unsigned char *datos, int cantidad)
{
    Estados siguienteEstado = EST_STX;
    unsigned char buffer[MAX_BUFFER];
    int indBuffer = 0, cantBuffer = 0;
    unsigned char chkBuffer = 0;
    int i;

    for (i = 0; i < cantidad; i++) {

        switch (siguienteEstado) {

        case EST_STX:
            if (datos[i] == STX) {
                indBuffer = 0;
                cantBuffer = 0;
                chkBuffer = 0;
                siguienteEstado = EST_CANT;
            }
            break;

        case EST_CANT:
            cantBuffer = datos[i];
            if (cantBuffer == 0)
                siguienteEstado = EST_CHK;
            else
                siguienteEstado = EST_DATOS;
            break;

        case EST_DATOS:
            buffer[indBuffer] = datos[i];
            indBuffer += 1;
            chkBuffer ^= datos[i] ;
            cantBuffer -= 1;
            if (cantBuffer == 0) {
                siguienteEstado = EST_CHK;
            }
            break;

        case EST_CHK:
            if (datos[i] == chkBuffer) {
                siguienteEstado = EST_ETX;
            }
            else {
                siguienteEstado = EST_STX;
            }
            break;

        case EST_ETX:
            if (datos[i] == ETX) {
                mostrarPaquete(buffer, indBuffer);
            }
            siguienteEstado = EST_STX;
            break;
        }
    }
}