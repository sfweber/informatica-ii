#include <stdio.h>

int main() {
    FILE *fp = fopen("teclado.txt", "w");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    int c;
    printf("Ingrese texto. Finalice con Ctrl+Z (Windows) o Ctrl+D (Linux):\n");

    while ((c = getchar()) != EOF) {
        fputc(c, fp);
    }

    fclose(fp);
    return 0;
}