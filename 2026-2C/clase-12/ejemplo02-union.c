#include <stdio.h>

int main(void) {
    union {
        unsigned char vec[4];
        float f;
    } x;

    //primera parte: cargamos el patron de bits 0x5F3759DF byte a byte
    //en x86 (little-endian) vec[0] es el byte MENOS significativo
    x.vec[3] = 0x5F;
    x.vec[2] = 0x37;
    x.vec[1] = 0x59;
    x.vec[0] = 0xDF;

    printf("Para los valores cargados:\n");
    printf("\nFlotante = %f = %e\n", x.f, x.f);

    printf("\nPresione ENTER para continuar\n");
    getchar();

    //segunda parte: al reves, ingresamos un flotante
    //y miramos los bytes que quedaron en memoria
    printf("Ahora ingrese un flotante:\n");
    scanf("%f", &x.f);

    printf("\nHexadecimal:     %02X %02X %02X %02X\n", x.vec[3], x.vec[2], x.vec[1], x.vec[0]);
    printf("En memoria (LE): %02X %02X %02X %02X\n", x.vec[0], x.vec[1], x.vec[2], x.vec[3]);
    printf("\nFlotante = %f = %e\n", x.f, x.f);

    return 0;
}
