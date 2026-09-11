/* INFO II - Resolucion del ejercicio 6 (slide 40)
 *
 *   "Al presionar [un boton] encender un led verde, al presionarlo nuevamente encender
 *    un led rojo, al presionarlo nuevamente encender ambos, al presionarlo nuevamente
 *    apagar todo y volver a empezar."
 *
 *   (En la slide dice "Al presionar un led": es una errata, va "un boton".)
 *
 * Funciones nuevas: NINGUNA. Concepto nuevo: NINGUNO. Es el ejercicio 4 con cuatro
 * estados en vez de dos y dos salidas en vez de una -> generalizar cuesta un case.
 *
 * Es Moore puro, y se ve en el codigo: las salidas NO se tocan en las transiciones.
 * La transicion solo cambia de estado; quien enciende y apaga es actualizarLeds(),
 * que mira el estado y nada mas.  salida = g(estado).
 *
 * Circuito: LED rojo en el pin 9, LED verde en el pin 10 (cada uno con su R de 1k),
 *           boton en el pin 8 con pull-down de 1k.
 */

#include <stdint.h>

const uint8_t ledRojo = 9;
const uint8_t ledVerde = 10;
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

/* --- estados de la APLICACION (no confundir con los del lector de boton) --- */
typedef enum {
    TODO_APAGADO,
    SOLO_VERDE,
    SOLO_ROJO,
    AMBOS
} APP_STATES;

APP_STATES appState = TODO_APAGADO;

/* --- prototipos --- */
EVENTOS leerBoton(void);
void actualizarLeds(void);

void setup() {
  pinMode( ledRojo , OUTPUT );
  pinMode( ledVerde , OUTPUT );
  pinMode( buttonPin , INPUT );
  actualizarLeds();
}

void loop() {
  EVENTOS evento;

  evento = leerBoton();

  if (evento == BOTON_PRESIONADO)
  {
    switch (appState) {
    case TODO_APAGADO:  appState = SOLO_VERDE;    break;
    case SOLO_VERDE:    appState = SOLO_ROJO;     break;
    case SOLO_ROJO:     appState = AMBOS;         break;
    case AMBOS:         appState = TODO_APAGADO;  break;
    }
    actualizarLeds();
  }
}

/* La salida depende SOLO del estado: esto es lo que hace que sea una maquina de Moore.
 * Se llama al entrar a cada estado (accion de entrada / "entry" en el diagrama). */
void actualizarLeds(void)
{
  switch (appState) {
  case TODO_APAGADO:  digitalWrite( ledVerde , LOW  );  digitalWrite( ledRojo , LOW  );  break;
  case SOLO_VERDE:    digitalWrite( ledVerde , HIGH );  digitalWrite( ledRojo , LOW  );  break;
  case SOLO_ROJO:     digitalWrite( ledVerde , LOW  );  digitalWrite( ledRojo , HIGH );  break;
  case AMBOS:         digitalWrite( ledVerde , HIGH );  digitalWrite( ledRojo , HIGH );  break;
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
