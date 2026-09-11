/* INFO II - Resolucion del ejercicio 5 (slide 40)
 *
 *   "Encender un led al presionar un boton. Hacerlo parpadear al volver a presionar.
 *    Apagar al volver a presionar."
 *
 * ESTE es el ejercicio que rompe delay(). El intento natural es:
 *
 *     case PARPADEANDO:
 *         digitalWrite(ledPin, HIGH);  delay(500);
 *         digitalWrite(ledPin, LOW);   delay(500);
 *
 * ...y el boton deja de responder durante un segundo entero. Probalo: la tercera
 * pulsacion se pierde si cae dentro de un delay. No hay sistema operativo que
 * atienda el boton por nosotros: loop() es el unico hilo de ejecucion que tenemos.
 *
 * La solucion es la misma idea de v5, aplicada dos veces:
 *   - un after(40 ms)  para el antirrebote   -> timeAntes    (adentro de leerBoton)
 *   - un after(500 ms) para el parpadeo      -> timeParpadeo (aca abajo)
 * Dos temporizadores independientes conviviendo, y NINGUN delay() en todo el sketch.
 * Eso es un superloop no bloqueante.
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

const uint32_t periodoMS = 500;          /* medio segundo prendido, medio apagado */

/* --- estados de la APLICACION (no confundir con los del lector de boton) --- */
typedef enum {
    APAGADO,
    ENCENDIDO,
    PARPADEANDO
} APP_STATES;

APP_STATES appState = APAGADO;
uint32_t timeParpadeo = 0;
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

  switch (appState) {

  case APAGADO:
      if (evento == BOTON_PRESIONADO)
      {
          appState = ENCENDIDO;
          digitalWrite( ledPin , HIGH );
      }
      break;

  case ENCENDIDO:
      if (evento == BOTON_PRESIONADO)
      {
          appState = PARPADEANDO;
          ledState = HIGH;                 /* arranca prendido */
          timeParpadeo = millis();         /* y arranca el reloj del parpadeo */
          digitalWrite( ledPin , ledState );   /* el entry: la salida sale del estado */
      }
      break;

  case PARPADEANDO:
      if (evento == BOTON_PRESIONADO)
      {
          appState = APAGADO;
          digitalWrite( ledPin , LOW );
      }
      else if ((uint32_t)(millis() - timeParpadeo) >= periodoMS)   /* after(500 ms) */
      {
          timeParpadeo = millis();
          ledState = !ledState;
          digitalWrite( ledPin , ledState );
      }
      break;
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
