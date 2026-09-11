/* Ejemplo 3 - v3 : antirrebote por ESPERA.
 *
 * El rebote son las laminas metalicas del pulsador chocando: entre 1 y 10 ms de
 * flancos falsos por cada pulsacion real. v2 los cuenta todos.
 *
 * La receta mas simple: cuando detecto un cambio, espero a que el contacto se calme
 * y VUELVO A LEER para confirmar. Si sigue distinto, el cambio era de verdad.
 *
 * 40 ms: mas que el rebote (1-10 ms) y menos que lo que tarda un dedo humano (~100 ms).
 *
 * EL COSTO, y es el tema de toda la clase que viene:
 *   delay(40) BLOQUEA. Durante 40 ms el micro no puede hacer absolutamente nada mas.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 8;
const uint8_t antireboteMS = 40;

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
    delay( antireboteMS );                    /* dejo que el contacto se calme */
    newValue = digitalRead( buttonPin );      /* y vuelvo a leer para confirmar */

    if (newValue != oldValue)                 /* si de verdad cambio... */
    {
      if (newValue == HIGH)
        digitalWrite( ledPin , HIGH );
      else
        digitalWrite( ledPin , LOW );
    }

    oldValue = newValue;
  }
}
