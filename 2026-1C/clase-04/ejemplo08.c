#include <stdio.h>

int main() {
    FILE *fp;
    char str[50];

    fp = fopen("numeros.txt", "r");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    if (fgets (str, sizeof(str), fp) == NULL)
    {
        perror ("Error al leer la entrada");
        fclose(fp);
        return 1;
    }
    printf ("%s", str);
    fclose(fp);
    return 0;
}
