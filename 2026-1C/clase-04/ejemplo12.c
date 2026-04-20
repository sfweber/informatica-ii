#include <stdio.h>
#include <unistd.h> 

int main() {
    FILE *fp = fopen("/mnt/pendrive/archivo_grande.txt", "r");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    int c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
        usleep(100);      
    }

    printf ("\nArchivo leido completamente... (?)\n");

    fclose(fp);
    return 0;
}