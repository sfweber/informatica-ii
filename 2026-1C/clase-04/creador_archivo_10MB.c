#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILESIZE_MB 10
#define BYTES_PER_MB (1024 * 1024)
#define TOTAL_BYTES (FILESIZE_MB * BYTES_PER_MB)

int main() {
    FILE *fp = fopen("archivo_grande.txt", "w"); 
    if (fp == NULL) {
        perror("No se pudo crear el archivo");
        return 1;
    }

    srand((unsigned int) time(NULL)); // Semilla para random

    for (int i = 0; i < TOTAL_BYTES; i++) {
        // Caracter aleatorio imprimible (entre 32 y 126 en ASCII)
        char c = (char)(rand() % (126 - 32 + 1) + 32);
        putc(c, fp);
    }

    fclose(fp);

    printf("Archivo de %d MB generado correctamente.\n", FILESIZE_MB);
    return 0;
}
