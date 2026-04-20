#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char linea[] = "23,45,67";
    char *token;
    int valor;

    token = strtok(linea, ",");

    while (token != NULL) {
        valor = atoi(token);
        printf("Valor: %d\n", valor);
        token = strtok(NULL, ",");
    }
    return 0;
}