/* Ejemplo 3 - v2 : deteccion de FLANCO, ahora si.
 *
 * Unico cambio respecto de v1: se actualiza la memoria (oldValue = newValue).
 * Sin eso, "recordar el valor anterior" no recuerda nada.
 *
 * Ojo: v2 se COMPORTA igual que v0 (el LED sigue al boton). La diferencia no se ve,
 * se razona: v0 escribe el pin decenas de miles de veces por segundo; v2 lo escribe
 * SOLO cuando algo cambia. Y, sobre todo, v2 ya tiene el mecanismo que el ejercicio 4
 * necesita: saber que hubo un flanco.
 *
 * Que le falta: el REBOTE. Activa "bounce" en el pulsador de Wokwi y mira que pasa.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 8;

uint8_t oldValue = LOW;

void setup() {
  pinMode( ledPin , OUTPUT );
  pinMode( buttonPin , INPUT );
}

void loop() {
  uint8_t newValue;

  newValue = digitalRead( buttonPin );

  if (newValue != oldValue)
  {
    if (newValue == HIGH)
      digitalWrite( ledPin , HIGH );
    else
      digitalWrite( ledPin , LOW );

    oldValue = newValue;
  }
}
