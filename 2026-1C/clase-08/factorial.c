#include <stdio.h>


// Funcion recursiva que calcula el factorial de n
int factorial ( int );

int main() {
    int numero = 5;
    printf("El factorial de %d es %d\n", numero, factorial(numero));
    return 0;
}
int factorial(int n) {
    if (n == 0) {
        // Caso base: el factorial de 0 es 1
        return 1;
    } else {
        // Caso recursivo: n * factorial de (n-1)
        return n * factorial(n - 1);
    }
}
