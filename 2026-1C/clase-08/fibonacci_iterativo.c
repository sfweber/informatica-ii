#include <stdio.h>

// Funcion iterativa para calcular el n-esimo termino de Fibonacci
int fibonacci_iterativo(int );

int main() {
    for (int i = 0; i < 46; i++) {
        printf("%15d", fibonacci_iterativo(i));
        if ((i + 1) % 5 == 0) // salto de linea cada 5 numeros
            printf("\n");
    }
    printf("\n");

    return 0;
}
int fibonacci_iterativo(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, resultado;
    for (int i = 2; i <= n; i++) {
        resultado = a + b;
        a = b;
        b = resultado;
    }
    return b;
}

