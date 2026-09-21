/* Ejemplo 04 - contar entradas a la ISR y avisar por el monitor serie cada 500.
 *
 * Mismo circuito que el 03, pero el generador va a 500 Hz (1 ms alto + 1 ms bajo):
 * a 5 Hz, 500 entradas son 100 segundos por mensaje y la demo no se ve.
 * A 500 Hz sale un mensaje por segundo.
 *
 * LA REGLA: la ISR no imprime. Solo cuenta.  contador++  y sale.
 * Serial.print() adentro de una ISR "funciona" en el core actual, pero se queda
 * esperando al UART con las interrupciones apagadas (HardwareSerial.cpp:256):
 * bloquea la ISR y viola la unica regla que tienen las ISR: ser cortas.
 * El loop() es el que mira el contador e imprime.
 *
 * Y ACA APARECE LA SECCION CRITICA. contador es uint16_t: DOS bytes en un micro
 * de 8 bits. El loop() los lee en dos instrucciones; si la ISR se mete entre
 * la primera y la segunda, la copia mezcla el byte bajo de una cuenta con el
 * byte alto de otra (p. ej. 0x01FF -> 0x0200: leo 0xFF, salta la ISR, leo 0x02,
 * y me queda 0x02FF, 256 de mas). noInterrupts()/interrupts() cierran esa
 * ventana. Es EXACTAMENTE lo que hace millis() con cli() (wiring.c:72),
 * y por eso millis() nunca devolvio un valor mezclado en la clase pasada.
 *
 * volatile SI va: contador la escribe la ISR y la lee el loop().
 * volatile no la hace atomica: para eso esta la seccion critica.
 */

#include <stdint.h>

const uint8_t emuPin = 4;
const uint8_t ledPin = 9;
const uint8_t intPin = 21;
const uint32_t semiperiodoMS = 1;     /* 1 ms alto + 1 ms bajo = 500 Hz */
const uint16_t cadaN = 500;           /* un mensaje cada 500 entradas = 1 por segundo */

uint32_t timeAntes = 0;
uint8_t emuState = LOW;
uint8_t ledState = LOW;

volatile uint16_t contador = 0;       /* la escribe la ISR, la lee el loop(): volatile */
uint16_t ultimoAviso = 0;             /* hasta que cuenta ya avisamos (solo el loop) */

/* --- prototipos --- */
void isrContar(void);

void setup() {
  pinMode( emuPin , OUTPUT );
  pinMode( ledPin , OUTPUT );
  pinMode( intPin , INPUT );
  digitalWrite( emuPin , LOW );
  digitalWrite( ledPin , LOW );
  Serial.begin( 115200 );

  attachInterrupt( digitalPinToInterrupt( intPin ) , isrContar , RISING );
}

void loop() {
  uint16_t copia;

  /* el generador: after(1 ms) invierte el pin 4 */
  if ((uint32_t)(millis() - timeAntes) >= semiperiodoMS)
  {
    timeAntes = millis();
    emuState = !emuState;
    digitalWrite( emuPin , emuState );
  }

  /* SECCION CRITICA: copiar los 2 bytes sin que la ISR se meta en el medio */
  noInterrupts();
  copia = contador;
  interrupts();

  /* la misma resta sin signo que con millis(): sobrevive al desborde de 65535 */
  if ((uint16_t)(copia - ultimoAviso) >= cadaN)
  {
    ultimoAviso = copia;
    Serial.print( "La ISR entro " );
    Serial.print( copia );
    Serial.println( " veces" );
  }
}

void isrContar(void)
{
  contador++;                         /* anotar y salir */
  ledState = !ledState;               /* (el LED a 250 Hz: se ve prendido a media luz) */
  digitalWrite( ledPin , ledState );
}
