/* Ejemplo 3 - v5 : la misma MEF, pero SIN BLOQUEAR.   <-- resolucion del ejercicio 3
 *
 * El delay(40) de v4 se reemplaza por una MARCA DE TIEMPO:
 *   - al entrar al estado de espera, anoto cuando fue      -> timeAntes = millis()
 *   - en cada vuelta pregunto si ya paso el tiempo         -> millis() - timeAntes >= 40
 * Mientras espero, el loop() sigue corriendo y puede hacer otras cosas.
 *
 * En la notacion de la catedra esto es el evento  after(40 ms)  de una timed FSM.
 *
 * millis() devuelve los milisegundos desde que arranco la placa (uint32_t). La cuenta
 * la lleva el Timer 0 dentro del core de Arduino (son los 9 bytes de variables globales
 * que reporta arduino-cli aunque tu sketch no declare ninguna).
 *
 * POR QUE LA RESTA Y NO  millis() >= timeAntes + 40 :
 *   millis() desborda a los ~49,7 dias y vuelve a 0. La suma se rompe en ese momento;
 *   la RESTA en aritmetica sin signo sigue dando el intervalo correcto igual.
 *   Es la unica forma de escribirlo que no tiene un bug cada 49 dias.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 8;
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
  pinMode( buttonPin , INPUT );
  digitalWrite( ledPin , LOW );
}

void loop() {
  uint8_t newValue;

  newValue = digitalRead( buttonPin );

  switch (NextState) {

  case buttonUp:
      if (newValue == HIGH)
      {
          NextState = buttonPressing;
          timeAntes = millis();
      }
      break;

  case buttonPressing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          newValue = digitalRead( buttonPin );
          if (newValue == HIGH)
          {
              NextState = buttonDown;
              digitalWrite( ledPin , HIGH );
          }
          else
              NextState = buttonUp;
      }
      break;

  case buttonDown:
      if (newValue == LOW)
      {
          NextState = buttonReleasing;
          timeAntes = millis();
      }
      break;

  case buttonReleasing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          newValue = digitalRead( buttonPin );
          if (newValue == LOW)
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
