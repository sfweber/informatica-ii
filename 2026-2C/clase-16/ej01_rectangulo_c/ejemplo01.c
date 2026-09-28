#include <stdio.h>

float obtenerLado(char lado);
float calcularArea(float ancho, float largo);
void mostrarResultado(float area);

int main() {
    float ancho, largo, area;
    // Obtener los valores de los lados
    ancho = obtenerLado('a');
    largo = obtenerLado('l');
    // Calcular el área
    area = calcularArea(ancho, largo);
    // Mostrar el resultado
    mostrarResultado(area);

    return 0;
}

// Función para obtener el valor de un lado del rectángulo
float obtenerLado(char lado) {
    float valor;
    printf("Introduce el valor del %s: ", lado == 'a' ? "ancho" : "largo");
    scanf("%f", &valor);
    return valor;
}

// Función para calcular el área del rectángulo
float calcularArea(float ancho, float largo) {
    return ancho * largo;
}

// Función para mostrar el resultado
void mostrarResultado(float area) {
    printf("El area del rectangulo es: %.2f\n", area);
}
