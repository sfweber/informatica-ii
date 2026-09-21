/* Ejemplo 02 - la primera ISR: un flanco enciende el LED.
 *
 * No hay boton: el pin 4 genera la senal y esta cableado al pin 21 (Wokwi no
 * tiene generador de senales). A los 2 segundos el pin 4 sube, UNA sola vez.
 * Ese flanco ascendente en el 21 dispara INT0 y la ISR enciende el LED.
 *
 * Tres cosas nuevas, y nada mas:
 *   attachInterrupt( digitalPinToInterrupt(pin), funcion, RISING )
 *   la ISR: una funcion sin parametros ni retorno, que NADIE llama desde el codigo
 *   el pin 21 en INPUT a secas: lo excita el pin 4, asi que no flota y no hace
 *   falta pull-up (eso es para un pin al que le cuelga un boton)
 *
 * Es un solo flanco en toda la vida del programa: para repetirlo, reiniciar.
 * Mientras el loop() esta "clavado" en delay(2000), el LED prende igual:
 * la ISR no depende de por donde este el loop().
 */

#include <stdint.h>

const uint8_t emuPin = 4;      /* genera la senal (emula un sensor / un boton) */
const uint8_t ledPin = 9;
const uint8_t intPin = 21;     /* D21 = pata 43 = PD0 = INT0 del chip = interrupcion #2 de Arduino */

/* --- prototipos --- */
void isrEnciende(void);

void setup() {
  pinMode( emuPin , OUTPUT );
  pinMode( ledPin , OUTPUT );
  pinMode( intPin , INPUT );          /* lo maneja el pin 4: no flota */
  digitalWrite( emuPin , LOW );
  digitalWrite( ledPin , LOW );

  attachInterrupt( digitalPinToInterrupt( intPin ) , isrEnciende , RISING );
}

void loop() {
  delay( 2000 );
  digitalWrite( emuPin , HIGH );      /* el flanco: LOW -> HIGH en el pin 21 */
}

/* La ISR. No la llama nadie: la llama el hardware cuando llega el flanco. */
void isrEnciende(void)
{
  digitalWrite( ledPin , HIGH );
}
