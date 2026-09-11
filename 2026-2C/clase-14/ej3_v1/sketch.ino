/* Ejemplo 3 - v1 : primer intento de detectar el FLANCO.  *** TIENE UN BUG A PROPOSITO ***
 *
 * Idea: no me interesa el nivel del boton, me interesa el INSTANTE en que cambia.
 * Para ver un cambio hay que recordar el valor anterior -> oldValue.
 *
 * EL BUG: oldValue nunca se actualiza. Queda en LOW para siempre.
 *   - Boton suelto : newValue = LOW  == oldValue -> no entra al if. LED queda como estaba.
 *   - Boton apretado: newValue = HIGH != oldValue -> entra y prende el LED.
 *   - Boton soltado : newValue = LOW  == oldValue -> NO entra. El LED se queda prendido.
 *
 * Resultado: prende y no apaga nunca mas.
 * ANTES DE CORRERLO: pedile al curso que prediga que va a pasar.
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

    /* FALTA:  oldValue = newValue;   <-- el bug esta aca */
  }
}
