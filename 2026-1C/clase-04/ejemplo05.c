#include <stdio.h>

int main() {
    FILE *fp;
    int i;
    char str[10];

    fp = fopen("nombre.txt", "w");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo de temperaturas");
        return 1;
    }

    printf("Ingrese su nombre [9 caracteres maximo]: ");
    scanf("%9s", str);

    for (i=0; str[i]!='\0'; i++)
    {
        fputc (str[i], fp);
    }
    fputc ('\n', fp);

    fclose(fp);
    return 0;
}