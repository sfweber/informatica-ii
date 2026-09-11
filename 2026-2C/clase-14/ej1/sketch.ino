/* INFO II - Resolucion del ejercicio 1 (slide 40 de "Introduccion a microcontroladores")
 *
 *   "Encender y apagar el LED de la placa cada 500 ms."
 *
 * Version de la practica guiada: LED_BUILTIN en vez del literal 13 (es un #define del
 * core, vale 13 en el Mega). Asi el mismo sketch anda en otra placa sin tocarlo.
 */

void setup() {
  pinMode( LED_BUILTIN , OUTPUT );      /* una vez */
}

void loop() {
  digitalWrite( LED_BUILTIN , HIGH );   /* y esto, para siempre */
  delay( 500 );
  digitalWrite( LED_BUILTIN , LOW );
  delay( 500 );
}
