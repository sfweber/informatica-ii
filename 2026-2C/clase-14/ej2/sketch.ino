/* INFO II - Resolucion del ejercicio 2 (slide 40 de "Introduccion a microcontroladores")
 *
 *   "Encender y apagar un LED conectado al pin 12 cada 500 ms."
 *
 * Version de la practica guiada: el pin en una const uint8_t (uint8_t es de C estandar,
 * <stdint.h>, no de Arduino). El LED lleva R de 1 k en serie: I = (5 - 2) V / 1 k = 3 mA.
 */

#include <stdint.h>                     /* C estandar: nos da uint8_t */

const uint8_t ledRojo = 12;

void setup() {
  pinMode( ledRojo , OUTPUT );
}

void loop() {
  digitalWrite( ledRojo , HIGH );
  delay( 500 );
  digitalWrite( ledRojo , LOW );
  delay( 500 );
}
