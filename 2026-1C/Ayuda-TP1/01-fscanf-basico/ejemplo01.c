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

    while (fscanf(fp, "%d %f %s", &num, &real, texto) == 3) {
        printf("Entero: %d, Flotante: %.2f, Texto: %s\n", num, real, texto);
    }

    fclose(fp);
    return 0;
}
