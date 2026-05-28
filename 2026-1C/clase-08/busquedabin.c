#include <stdio.h>

int busquedaBinaria(int[], int, int, int);

int main() {
    int datos[] = {1, 3, 5, 7, 9, 11, 13};
    int n = sizeof(datos) / sizeof(datos[0]);
    int objetivo = 8;

    int resultado = busquedaBinaria(datos, 0, n - 1, objetivo);

    if (resultado != -1)
        printf("Elemento encontrado en la posicion %d\n", resultado);
    else
        printf("Elemento no encontrado\n");

    return 0;
}

int busquedaBinaria(int vec[], int izquierda, int derecha, int objetivo) {
    if (izquierda > derecha) {
        return -1; // Caso base: el objetivo no está en el arreglo
    }

    int medio = (izquierda + derecha)  / 2;

    if (vec[medio] == objetivo) {
        return medio; // Elemento encontrado
    } else if (objetivo < vec[medio]) {
        // Buscar en la mitad izquierda
        return busquedaBinaria(vec, izquierda, medio - 1, objetivo);
    } else {
        // Buscar en la mitad derecha
        return busquedaBinaria(vec, medio + 1, derecha, objetivo);
    }
}
