/* Ejemplo 03 - una senal cuadrada de 5 Hz y una ISR que invierte el LED.
 *
 * El pin 4 hace 100 ms alto + 100 ms bajo (periodo 200 ms = 5 Hz, 50 %),
 * escrito con millis() como en la clase pasada: sin delay(), el loop() sigue vivo.
 * Cada flanco ASCENDENTE (5 por segundo) entra a la ISR, que invierte el LED.
 * El LED cambia 5 veces por segundo: se lo ve parpadear a 2,5 Hz.
 *
 * Sobre ledState: la lee y la escribe SOLO la ISR. No la comparte con el loop(),
 * asi que NO lleva volatile. volatile es para lo que se comparte entre la ISR y
 * el programa principal (ejemplo 04). Ponerlo aca no rompe nada, pero ensena mal.
 *
 * El orden importa: primero invertir, despues escribir. Al reves, el LED muestra
 * el estado ANTERIOR y el primer flanco no hace nada visible.
 */

#include <stdint.h>

const uint8_t emuPin = 4;
const uint8_t ledPin = 9;
const uint8_t intPin = 21;
const uint32_t semiperiodoMS = 100;   /* 100 ms alto + 100 ms bajo = 5 Hz */

uint32_t timeAntes = 0;
uint8_t emuState = LOW;               /* estado del generador (lo usa solo el loop) */
uint8_t ledState = LOW;               /* estado del LED (lo usa solo la ISR) */

/* --- prototipos --- */
void isrToggle(void);

void setup() {
  pinMode( emuPin , OUTPUT );
  pinMode( ledPin , OUTPUT );
  pinMode( intPin , INPUT );
  digitalWrite( emuPin , LOW );
  digitalWrite( ledPin , LOW );

  attachInterrupt( digitalPinToInterrupt( intPin ) , isrToggle , RISING );
}

void loop() {
  /* el generador: after(100 ms) invierte el pin 4 */
  if ((uint32_t)(millis() - timeAntes) >= semiperiodoMS)
  {
    timeAntes = millis();
    emuState = !emuState;
    digitalWrite( emuPin , emuState );
  }
}

void isrToggle(void)
{
  ledState = !ledState;               /* primero invertir... */
  digitalWrite( ledPin , ledState );  /* ...despues escribir */
}
