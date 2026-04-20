#include <stdio.h>

int main() {
    FILE *fp;
    int dia, mes, anio;
    fp = fopen("fechas.txt", "r");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    if (fscanf (fp, "%d/%d/%d", &dia, &mes, &anio) == 3)
    {
        printf ("fecha: %d/%d/%d\n", dia, mes, anio);
        fclose (fp);
        return 0;
    }
    else
    {
        printf ("Formato inesperado o fin de archivo.\n");
        fclose(fp);
        return 1;
    }
}
