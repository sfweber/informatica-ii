/* Ejemplo 05 - el "tipico": el ejercicio 5 de la clase pasada, con interrupcion.
 *
 *   "Encender un led al presionar un boton. Hacerlo parpadear al volver a presionar.
 *    Apagar al volver a presionar."   (mismo enunciado que Intro_ej5 de la clase 14)
 *
 * Es Intro_ej5 con UNA diferencia: el driver leerBoton() ya no pregunta por el pin
 * en cada vuelta. La ISR le avisa. La aplicacion (APAGADO -> ENCENDIDO -> PARPADEANDO)
 * es identica, linea por linea.
 *
 * CIRCUITO: el de v6 (pin 21 + INPUT_PULLUP, presionado = LOW). Sin resistencia.
 *
 * LO QUE HAY QUE VER:
 *   1) El rebote NO se fue: EMPEORO. Con CHANGE la ISR dispara en CADA rebote,
 *      decenas de veces por pulsacion (ver la cuenta en la simulacion).
 *   2) Adentro de la ISR no hay delay() (delay espera a millis(), y millis()
 *      no avanza mientras las interrupciones estan apagadas: se cuelga).
 *      => el antirrebote TIENE que ser el de la clase pasada: la MEF con millis().
 *   3) La ISR hace UNA cosa: hayFlanco = 1. Anotar y salir.
 *      "La interrupcion dice CUANDO paso algo; la maquina de estados recuerda
 *       DONDE estabas y decide QUE hacer."
 *   4) La MEF no le pregunta a la ISR QUE flanco fue: ya sabe cual espera
 *      (en buttonUp solo puede ser una presion). A los 40 ms LEE EL PIN y confirma.
 *      Por eso no hace falta guardar el nivel en la ISR.
 *
 * hayFlanco es UN byte: escribirlo y leerlo es atomico en el AVR, y por eso aca
 * no hace falta noInterrupts() (comparar con el contador de 16 bits del ej. 04).
 * Orden dentro del driver: PRIMERO limpiar la bandera, DESPUES leer el pin. Asi,
 * un flanco que caiga justo en el medio queda anotado para el proximo estado en
 * vez de perderse.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t buttonPin = 21;          /* D21 = INT0 del chip = interrupcion #2 de Arduino */
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
volatile uint8_t hayFlanco = 0;        /* la escribe la ISR, la lee el driver: volatile */

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
void isrBoton(void);

void setup() {
  pinMode( ledPin , OUTPUT );
  pinMode( buttonPin , INPUT_PULLUP );
  digitalWrite( ledPin , LOW );

  attachInterrupt( digitalPinToInterrupt( buttonPin ) , isrBoton , CHANGE );
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
 *  El LECTOR DE BOTON de la clase pasada, con la ISR en vez del polling.
 *  Cambian SEIS lineas: desaparece el digitalRead() de cada vuelta, y en los
 *  dos estados de reposo el evento es "hubo un flanco" en vez de "el pin
 *  cambio". La confirmacion a los 40 ms queda igual: ahi SI se lee el pin.
 * ------------------------------------------------------------------ */
EVENTOS leerBoton(void)
{
  uint8_t newValue;
  EVENTOS evento;

  evento = SIN_EVENTO;

  switch (NextState) {

  case buttonUp:
      if (hayFlanco)                           /* la ISR avisa: algo paso en el pin */
      {
          hayFlanco = 0;
          NextState = buttonPressing;
          timeAntes = millis();
      }
      break;

  case buttonPressing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          hayFlanco = 0;                       /* los rebotes de estos 40 ms la volvieron a levantar */
          newValue = digitalRead( buttonPin ); /* y ahora si: leer para confirmar */
          if (newValue == LOW)                 /* LOW = presionado (pull-up) */
          {
              NextState = buttonDown;
              evento = BOTON_PRESIONADO;      /* <-- el flanco confirmado */
          }
          else
              NextState = buttonUp;           /* era un rebote (o un pulso muy corto) */
      }
      break;

  case buttonDown:
      if (hayFlanco)
      {
          hayFlanco = 0;
          NextState = buttonReleasing;
          timeAntes = millis();
      }
      break;

  case buttonReleasing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          hayFlanco = 0;
          newValue = digitalRead( buttonPin );
          if (newValue == HIGH)                /* HIGH = soltado */
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

/* La ISR: anotar y salir. Ni LED, ni estados, ni millis(), ni delay(). */
void isrBoton(void)
{
  hayFlanco = 1;
}
