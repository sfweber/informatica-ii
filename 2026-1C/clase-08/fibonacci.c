#include <stdio.h>

// Funcion recursiva que calcula el n-esimo termino Fibonacci
int fibonacci(int );

int main() {
    int n ;
    printf ("ingrese n: ");
    scanf ("%d", &n);
    printf("\n\nEl termino %d de Fibonacci es %d\n", n, fibonacci(n));
    return 0;
}

int fibonacci(int n) {
    if (n == 0) {
        return 0;               // Caso base 1: F(0) = 0
    } else if (n == 1) {
        return 1;               // Caso base 2: F(1) = 1
    } else {
        // Caso recursivo: F(n) = F(n-1) + F(n-2)
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
