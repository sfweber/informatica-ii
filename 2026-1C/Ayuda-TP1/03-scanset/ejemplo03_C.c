/*Espacio antes de %100[^,]: El espacio al principio de la cadena de formato " %100[^,],%d,%f" le dice a fscanf que 
ignore cualquier espacio en blanco, incluidos saltos de línea (\n), tabulaciones o espacios antes del próximo valor.
*/

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

    while (fscanf(fp, " %100[^,] , %d , %f", texto, &num, &real) == 3) {
        printf("Texto: %s, Entero: %d, Flotante: %.2f\n", texto, num, real);
    }

    fclose(fp);
    return 0;
}
