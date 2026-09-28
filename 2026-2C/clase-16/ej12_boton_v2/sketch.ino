/* INFO II - C++ I - El boton como CLASE (dos botones)
 *
 *   Dos botones, dos LEDs: cada pulsacion prende o apaga su LED. Anda tambien
 *   apretando los dos juntos.
 *
 * QUE CAMBIA respecto del ejemplo de un boton: UNA linea del boton,
 *
 *     Boton b2( 20 );
 *
 * y el resto es del LED y de la aplicacion (11 lineas en total). Duplicando a mano,
 * sin clase, el segundo boton cuesta 66 lineas y la maquina de estados copiada entera.
 *
 * El mismo molde, dos objetos. Cada uno tiene su maquina de estados adentro y su
 * propio tiempo de antirrebote: b1 no puede tocar el estado de b2 ni aunque quiera.
 * Si el boton 2 rebotara mas, alcanza con `Boton b2( 20 , 60 );`.
 */

#include <stdint.h>

const uint8_t ledPin = 9;
const uint8_t ledPin2 = 10;

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
Boton b2( 20 );

uint8_t ledState = LOW;
uint8_t ledState2 = LOW;

void setup() {
  pinMode( ledPin , OUTPUT );
  digitalWrite( ledPin , LOW );
  pinMode( ledPin2 , OUTPUT );
  digitalWrite( ledPin2 , LOW );
}

void loop() {
  Boton::EVENTOS evento;

  evento = b1.leer();

  if (evento == Boton::BOTON_PRESIONADO)
  {
    ledState = !ledState;               /* '!' logico: LOW->1, HIGH->0. NO es '~' */
    digitalWrite( ledPin , ledState );
  }

  evento = b2.leer();

  if (evento == Boton::BOTON_PRESIONADO)
  {
    ledState2 = !ledState2;
    digitalWrite( ledPin2 , ledState2 );
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
