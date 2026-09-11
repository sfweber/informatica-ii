/* Ejemplo 3 - v4 : el antirrebote como MAQUINA DE ESTADOS (clase 7).
 *
 * Mismo comportamiento que v3, pero el "en que paso voy" deja de estar escondido
 * en el anidamiento de ifs y pasa a ser una variable CON NOMBRE.
 *
 *   buttonUp        boton suelto        (LED apagado)
 *   buttonPressing  detecte que bajo    (esperando confirmar)
 *   buttonDown      boton presionado    (LED encendido)
 *   buttonReleasing detecte que subio   (esperando confirmar)
 *
 * Diagrama (notacion de la catedra: evento [guarda] / accion):
 *   ../diagramas/mef-antirrebote.svg
 *
 * Plantilla: 7.C_Maquinas de estado/formato_FSM.c  (typedef enum STATES + switch).
 * El break del switch es la excepcion aceptada a la convencion "sin break".
 *
 * Que le falta TODAVIA: el delay(40) sigue adentro. La MEF ordeno el codigo,
 * no destrabo el bloqueo.  ->  v5
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 8;
const uint8_t antireboteMS = 40;

typedef enum {
    buttonUp,
    buttonPressing,
    buttonDown,
    buttonReleasing
} STATES;

STATES NextState = buttonUp;

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
          NextState = buttonPressing;
      break;

  case buttonPressing:
      delay( antireboteMS );
      newValue = digitalRead( buttonPin );
      if (newValue == HIGH)
      {
          NextState = buttonDown;
          digitalWrite( ledPin , HIGH );
      }
      else
          NextState = buttonUp;         /* era un rebote: vuelvo sin hacer nada */
      break;

  case buttonDown:
      if (newValue == LOW)
          NextState = buttonReleasing;
      break;

  case buttonReleasing:
      delay( antireboteMS );
      newValue = digitalRead( buttonPin );
      if (newValue == LOW)
      {
          NextState = buttonUp;
          digitalWrite( ledPin , LOW );
      }
      else
          NextState = buttonDown;       /* era un rebote */
      break;
  }
}
