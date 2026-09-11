/* Ejemplo 3 - v6 : la MISMA maquina, en el pin 21 y con PULL-UP INTERNO.
 *
 * Es el puente con la clase de interrupciones: el pin 21 es uno de los pines de
 * interrupcion externa del Mega (D2, D3, D18, D19, D20, D21), asi que este es el
 * circuito con el que vamos a arrancar la clase que viene.
 *
 * DOS CAMBIOS, y ninguno es de la maquina de estados:
 *   1) HARDWARE: no hay resistencia externa. El boton va del pin 21 a GND y listo.
 *      La resistencia la pone el ATmega adentro (20 a 50 kOhm, datasheet Tabla 31.1).
 *      Ojo: el chip tiene pull-UP interno; pull-DOWN interno NO existe (Tabla 13-1).
 *   2) LOGICA INVERTIDA: en reposo el pull-up deja el pin en 5V -> suelto = HIGH.
 *      Al presionar, el boton lo lleva a masa            -> presionado = LOW.
 *      Por eso todos los HIGH/LOW de las comparaciones estan al reves que en v5.
 *
 * Los nombres de los estados NO cambian, y ese es el punto: describen al BOTON
 * (arriba / bajando / abajo / subiendo), no al nivel electrico. Sobreviven al cambio.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 21;
const uint32_t antireboteMS = 40;

typedef enum {
    buttonUp,
    buttonPressing,
    buttonDown,
    buttonReleasing
} STATES;

STATES NextState = buttonUp;
uint32_t timeAntes = 0;

void setup() {
  pinMode( ledPin , OUTPUT );
  pinMode( buttonPin , INPUT_PULLUP );      /* <-- el unico cambio del setup */
  digitalWrite( ledPin , LOW );
}

void loop() {
  uint8_t newValue;

  newValue = digitalRead( buttonPin );

  switch (NextState) {

  case buttonUp:
      if (newValue == LOW)                  /* LOW = presionado */
      {
          NextState = buttonPressing;
          timeAntes = millis();
      }
      break;

  case buttonPressing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          newValue = digitalRead( buttonPin );
          if (newValue == LOW)
          {
              NextState = buttonDown;
              digitalWrite( ledPin , HIGH );
          }
          else
              NextState = buttonUp;
      }
      break;

  case buttonDown:
      if (newValue == HIGH)                 /* HIGH = soltado */
      {
          NextState = buttonReleasing;
          timeAntes = millis();
      }
      break;

  case buttonReleasing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          newValue = digitalRead( buttonPin );
          if (newValue == HIGH)
          {
              NextState = buttonUp;
              digitalWrite( ledPin , LOW );
          }
          else
              NextState = buttonDown;
      }
      break;
  }
}
