/* INFO II - Resolucion del ejercicio 4 (slide 40)
 *
 *   "Encender un led al presionar un boton. Apagar al volver a presionar."
 *
 * QUE CAMBIA respecto del ejercicio 3, y es lo unico importante de este ejercicio:
 * la salida deja de ser funcion de la ENTRADA y pasa a ser funcion del ESTADO.
 * El boton ya no dice "prendete": dice "cambiate". Para saber a que, hay que
 * recordar como estabas -> ledState.  (Eso es una maquina de Moore.)
 *
 * Funciones nuevas de Arduino: NINGUNA. Todo lo que hace falta ya lo escribimos.
 *
 * El refactor: separamos el LECTOR DE BOTON (la MEF del ejercicio 3, que ahora
 * devuelve un evento) de la APLICACION (que decide que hacer con ese evento).
 * Dos maquinas, una responsabilidad cada una.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 8;
const uint32_t antireboteMS = 40;

/* --- estados del lector de boton (el antirrebote del ejercicio 3) --- */
typedef enum {
    buttonUp,
    buttonPressing,
    buttonDown,
    buttonReleasing
} STATES;

/* --- lo que el lector de boton le informa a la aplicacion --- */
typedef enum {
    SIN_EVENTO,
    BOTON_PRESIONADO,
    BOTON_SOLTADO
} EVENTOS;

STATES NextState = buttonUp;
uint32_t timeAntes = 0;

uint8_t ledState = LOW;

/* --- prototipos --- */
EVENTOS leerBoton(void);

void setup() {
  pinMode( ledPin , OUTPUT );
  pinMode( buttonPin , INPUT );
  digitalWrite( ledPin , LOW );
}

void loop() {
  EVENTOS evento;

  evento = leerBoton();

  if (evento == BOTON_PRESIONADO)
  {
    ledState = !ledState;               /* '!' logico: LOW->1, HIGH->0. NO es '~' */
    digitalWrite( ledPin , ledState );
  }
}
/* ------------------------------------------------------------------ *
 *  El LECTOR DE BOTON, tal cual quedo en el ejercicio 3 (v5).
 *  Es una maquina de estados que se ocupa de UNA sola cosa: mirar el pin,
 *  aguantar el rebote sin bloquear, y avisar cuando hubo un cambio de verdad.
 *  De aca en adelante no se toca mas: los ejercicios 4, 5 y 6 la usan igual.
 * ------------------------------------------------------------------ */
EVENTOS leerBoton(void)
{
  uint8_t newValue;
  EVENTOS evento;

  newValue = digitalRead( buttonPin );
  evento = SIN_EVENTO;

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
              evento = BOTON_PRESIONADO;      /* <-- el flanco confirmado */
          }
          else
              NextState = buttonUp;           /* era un rebote */
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
              evento = BOTON_SOLTADO;
          }
          else
              NextState = buttonDown;
      }
      break;
  }

  return evento;
}
