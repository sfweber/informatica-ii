#include <stdio.h>
#include <string.h>

int esLetraONum(char c) {
    return ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9'));
}

int main() {
    FILE *fp = fopen("logs_ups.txt", "r");
    if (!fp) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    const char objetivo[] = "UPM";
    char buffer[100];
    int idx = 0;
    int c, contador = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (esLetraONum(c)) {
            if (idx < (sizeof(buffer) - 1)) {
                buffer[idx] = c;
                idx++;
                buffer[idx] = '\0';
            }
        } else {
            if (idx > 0) {
                if (strcmp(buffer, objetivo) == 0) {
                    contador++;
                }
                idx = 0;
                buffer[0] = '\0';
            }
        }
    }

    // Por si termina justo con la palabra
    if (idx > 0 && strcmp(buffer, objetivo) == 0) {
        contador++;
    }

    fclose(fp);

    if (contador > 0) {
        printf("La palabra '%s' aparece %d veces.\n", objetivo, contador);
    } else {
        printf("La palabra '%s' no se encontró.\n", objetivo);
    }

    return 0;
}
