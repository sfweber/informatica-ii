#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Este es un ejemplo de strtok";
    char *token;

    // Primer token
    token = strtok(str, " ");

    // Imprimir cada token
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " ");
    }

    getchar();
    return 0;
}
