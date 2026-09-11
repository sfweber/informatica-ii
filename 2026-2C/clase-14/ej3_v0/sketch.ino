/* Ejemplo 3 - v0 : el LED sigue al boton, leyendo POR NIVEL.
 *
 * Ejercicio 3 de la slide 40: "Encender un led al mantener presionado un boton.
 * Apagar al liberar."
 *
 * Circuito:  LED rojo en el pin 9, con R de 1k en serie a GND.
 *            Boton entre 5V y el pin 8, con R de 1k de PULL-DOWN del pin 8 a GND.
 *            Logica DIRECTA: presionado = HIGH, suelto = LOW.
 *
 * Que ensena:  pinMode(..., INPUT) y digitalRead().
 * Que le falta: nada para ESTE ejercicio. Falla recien en el ejercicio 4,
 *               donde hace falta el INSTANTE del cambio y no el nivel.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 8;

void setup() {
  pinMode( ledPin , OUTPUT );
  pinMode( buttonPin , INPUT );
}

void loop() {
  uint8_t newValue;

  newValue = digitalRead( buttonPin );

  if (newValue == HIGH)
    digitalWrite( ledPin , HIGH );
  else
    digitalWrite( ledPin , LOW );
}
