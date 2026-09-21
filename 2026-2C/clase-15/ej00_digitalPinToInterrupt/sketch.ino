/* Ejemplo 00 - digitalPinToInterrupt(): que pines del Mega pueden interrumpir?
 *
 * Hay CUATRO numeraciones distintas para la misma cosa, y esta es la slide que
 * las pone en fila:
 *   pata del chip 43  ->  puerto PD0  ->  INT0 del ATmega  ->  D21 en la placa
 *   ... y attachInterrupt() no usa NINGUNO de esos numeros: usa la "interrupcion #"
 *   de Arduino, que en el Mega es OTRA lista (D2->0, D3->1, D21->2, D20->3, D19->4, D18->5).
 *
 * digitalPinToInterrupt(pin) hace esa traduccion. Es un #define del core, no una
 * funcion: variants/mega/pins_arduino.h:110. Para un pin que no puede interrumpir
 * devuelve NOT_AN_INTERRUPT (-1, Arduino.h:189).
 *
 * NUM_DIGITAL_PINS vale 70 en el Mega (pins_arduino.h:28): D0-D53 mas A0-A15.
 *
 * Salida esperada en el monitor serie (115200):
 *   Pin digital 2 -> interrupcion #0
 *   Pin digital 3 -> interrupcion #1
 *   Pin digital 18 -> interrupcion #5
 *   Pin digital 19 -> interrupcion #4
 *   Pin digital 20 -> interrupcion #3
 *   Pin digital 21 -> interrupcion #2
 */

#include <stdint.h>

void setup() {
  uint8_t pin;

  Serial.begin( 115200 );

  for (pin = 0; pin < NUM_DIGITAL_PINS; pin++)
  {
    if (digitalPinToInterrupt( pin ) != NOT_AN_INTERRUPT)
    {
      Serial.print( "Pin digital " );
      Serial.print( pin );
      Serial.print( " -> interrupcion #" );
      Serial.println( digitalPinToInterrupt( pin ) );
    }
  }
}

void loop() {
}
