/* INFO II - C++ I - El boton como CLASE (un boton)
 *
 *   Mismo comportamiento que el ejercicio 4 de la clase 14, en pull-up (pin 21,
 *   presionado = LOW): un LED que se prende y se apaga con cada pulsacion.
 *
 * QUE CAMBIA respecto del ejercicio 4, y es lo unico importante de este ejemplo:
 * TODO lo que era del boton y estaba suelto en el ambito global (buttonPin,
 * antireboteMS, NextState, timeAntes, los dos enum y leerBoton()) pasa a vivir
 * adentro de `class Boton`. Afuera no queda nada del boton.
 *
 *   - PRIVADO (lo que el boton se acuerda de si mismo, nadie de afuera lo toca):
 *       STATES        la lista de estados de la maquina (solo leer() la usa)
 *       pin           la identidad del boton: que pin es
 *       antireboteMS  cuanto aguanta el rebote ESTE boton
 *       nextState     el estado actual de la maquina
 *       timeAntes     el reloj del antirrebote
 *     b1.nextState = ... no compila.
 *
 *   - PUBLICO (lo unico que la aplicacion ve):
 *       EVENTOS       lo que el boton le informa a la aplicacion: es el contrato
 *                     con loop(), por eso es publico. Desde afuera se escribe
 *                     Boton::EVENTOS y Boton::BOTON_PRESIONADO (es "de la clase").
 *       Boton( pin , antirebote = 40 )  el constructor: guarda el pin y el tiempo
 *                     de antirrebote, arranca la maquina en buttonUp con el reloj
 *                     en cero y hace el pinMode. El antirrebote tiene valor por
 *                     defecto (como cFecha en ej11): Boton b( 21 ) usa 40 ms,
 *                     Boton b( 21 , 60 ) usa 60. Sin pin no se puede crear.
 *       leer()        es leerBoton() de siempre.
 *
 * La maquina de estados no cambia ni una linea de logica: solo cambia de quien es
 * el estado. `Boton b1( 21 );` crea el boton; `b1.leer()` lo lee.
 */

#include <stdint.h>

const uint8_t ledPin = 9;

class Boton
{
private:
    /* --- estados del lector de boton (el antirrebote del ejercicio 3) --- */
    enum STATES {                       /* solo leer() lo usa */
        buttonUp,
        buttonPressing,
        buttonDown,
        buttonReleasing
    };

    uint8_t pin;                        /* identidad: que pin es */
    uint32_t antireboteMS;              /* cuanto aguanta el rebote ESTE boton */
    STATES nextState;                   /* estado actual de la maquina */
    uint32_t timeAntes;                 /* reloj del antirrebote */

public:
    /* --- lo que el boton le informa a la aplicacion: el contrato con loop() --- */
    enum EVENTOS {
        SIN_EVENTO,
        BOTON_PRESIONADO,
        BOTON_SOLTADO
    };

    Boton( uint8_t p , uint32_t antirebote = 40 );
    EVENTOS leer( void );
};

Boton b1( 21 );

uint8_t ledState = LOW;

void setup() {
  pinMode( ledPin , OUTPUT );
  digitalWrite( ledPin , LOW );
}

void loop() {
  Boton::EVENTOS evento;

  evento = b1.leer();

  if (evento == Boton::BOTON_PRESIONADO)
  {
    ledState = !ledState;               /* '!' logico: LOW->1, HIGH->0. NO es '~' */
    digitalWrite( ledPin , ledState );
  }
}
/* ------------------------------------------------------------------ *
 *  Los metodos de Boton, definidos afuera de la clase (Boton::).
 *  El constructor arma el boton al crearlo: los cinco atributos quedan con
 *  valor y el pin configurado. El valor por defecto del antirrebote va SOLO en
 *  la declaracion (arriba, en la clase), no aca.
 *  leer() es el LECTOR DE BOTON de la clase 14 (ejercicio 3, v6): mira el pin,
 *  aguanta el rebote sin bloquear y avisa cuando hubo un cambio de verdad.
 *  No cambio ni una linea de logica.
 * ------------------------------------------------------------------ */
Boton::Boton( uint8_t p , uint32_t antirebote )
{
  pin = p;
  antireboteMS = antirebote;
  nextState = buttonUp;
  timeAntes = 0;
  pinMode( pin , INPUT_PULLUP );
}

Boton::EVENTOS Boton::leer( void )
{
  uint8_t newValue;
  EVENTOS evento;

  newValue = digitalRead( pin );
  evento = SIN_EVENTO;

  switch (nextState) {

  case buttonUp:
      if (newValue == LOW)
      {
          nextState = buttonPressing;
          timeAntes = millis();
      }
      break;

  case buttonPressing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          newValue = digitalRead( pin );
          if (newValue == LOW)
          {
              nextState = buttonDown;
              evento = BOTON_PRESIONADO;      /* <-- el flanco confirmado */
          }
          else
              nextState = buttonUp;           /* era un rebote */
      }
      break;

  case buttonDown:
      if (newValue == HIGH)
      {
          nextState = buttonReleasing;
          timeAntes = millis();
      }
      break;

  case buttonReleasing:
      if ((uint32_t)(millis() - timeAntes) >= antireboteMS)
      {
          newValue = digitalRead( pin );
          if (newValue == HIGH)
          {
              nextState = buttonUp;
              evento = BOTON_SOLTADO;
          }
          else
              nextState = buttonDown;
      }
      break;
  }

  return evento;
}
