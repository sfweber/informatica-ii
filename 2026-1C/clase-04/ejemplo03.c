#include <stdio.h>
#include <errno.h>

int main() {
    FILE *fp = fopen("datos.txt", "w");
    if (fp == NULL) {
        perror ("Error abriendo archivo");
        return 1;
    }

    char nombre[] = "Alice";
    int edad = 30;

    fprintf (fp, "Nombre: %s, Edad: %d", nombre, edad);

    fclose(fp);
    return 0;
}