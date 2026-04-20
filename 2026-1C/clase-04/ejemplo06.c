#include <stdio.h>

int main() {
    FILE *fp;
    char mensaje[] = "Este es un mensaje con fputs.\n";

    fp = fopen("mensaje.txt", "a");  // modo append
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    if (fputs(mensaje, fp) == EOF) {
        perror("Error al escribir con fputs");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    printf("Mensaje guardado con fputs.\n");
    return 0;
}
