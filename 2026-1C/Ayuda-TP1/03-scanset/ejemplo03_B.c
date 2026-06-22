#include <stdio.h>

int main() {
    FILE *fp;
    int num;
    float real;
    char texto[100];

    fp = fopen("datos.txt", "r");

    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    while (fscanf(fp, "%100[^,], %d, %f", texto, &num, &real) == 3) {
        printf("Texto: %s, Entero: %d, Flotante: %.2f\n", texto, num, real);
    }

    fclose(fp);
    return 0;
}
