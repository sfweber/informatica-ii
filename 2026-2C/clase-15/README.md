# Clase 15

**Tema:** **Interrupciones de hardware.** Qué pines pueden interrumpir y con qué número (`digitalPinToInterrupt`), cómo se escribe una ISR y qué no va adentro, `volatile` y **sección crítica**, y cómo la interrupción se conecta con la máquina de estados del antirrebote de la clase 14 **sin tocar la aplicación**. Arduino Mega 2560 en **Wokwi**, a nivel de la API del core.

Arrancamos donde terminó la clase 14: [`v6`](../clase-14/ej3_v6_pin21_pullup/), botón en el **pin 21** con `INPUT_PULLUP`. El 21 es uno de los seis pines de interrupción externa del Mega, y por eso la clase pasada cerró ahí.

## Cómo correrlos

Cada carpeta es un proyecto de Wokwi completo: `sketch.ino` (el código) y `diagram.json` (el circuito).

* **En Wokwi:** https://wokwi.com → *New Project* → *Arduino Mega* → pegar `sketch.ino` en la pestaña del código y `diagram.json` en la pestaña `diagram.json`. (Los pulsadores tienen `"bounce": "1"` para que el rebote **se vea**.)
* **En la placa real:** arduino-cli exige que el archivo se llame como la carpeta → `mv sketch.ino <carpeta>.ino`, y adentro de la carpeta:
  ```bash
  arduino-cli compile --fqbn arduino:avr:mega .
  arduino-cli upload  --fqbn arduino:avr:mega -p /dev/ttyUSB0 .
  ```

| Ejemplos | Circuito |
|---|---|
| `ej00` | sólo la placa |
| `ej02`, `ej03`, `ej04` | LED en el **pin 9** con 1 kΩ y **un cable del pin 4 al 21**. Sin botón: el sketch genera la señal, porque Wokwi no tiene generador |
| `ej05` | **botón del pin 21 a GND, sin resistencia** (`INPUT_PULLUP`, presionado = `LOW`); LED en el 9 con 1 kΩ |

> ⚠️ **Si venís del circuito de la clase 14 (pin 8 + pull-down), el cambio de cable va primero:** mover el botón **del pin 8 al 21**, borrar la resistencia de pull-down y llevar la otra pata a GND. `attachInterrupt()` sobre un pin que no es de interrupción **no da error ni aviso: no hace nada**. Si el botón se queda en el 8, el LED no responde y no hay nada en pantalla que lo explique.

## ej00 — [¿qué pines pueden interrumpir?](ej00_digitalPinToInterrupt/)

Recorre los 70 pines del Mega y lista los que tienen interrupción externa.
Probar: monitor serie a **115200**, salen seis líneas.

```
Pin digital 2 -> interrupcion #0      Pin digital 19 -> interrupcion #4
Pin digital 3 -> interrupcion #1      Pin digital 20 -> interrupcion #3
Pin digital 18 -> interrupcion #5     Pin digital 21 -> interrupcion #2
```

**`digitalPinToInterrupt(21)` devuelve `2`, no `0`** —aunque el 21 sea `INT0` del chip— porque la numeración de `attachInterrupt()` es la de Arduino, histórica (viene del UNO, donde la 0 era el pin 2). De ahí la regla: **el número nunca se escribe a mano.** `attachInterrupt(0, …)` «porque es INT0» engancha el pin **2**.

`digitalPinToInterrupt()` no es una función, es un `#define` del core; para un pin que no interrumpe devuelve `NOT_AN_INTERRUPT` (`-1`). INT6 e INT7 existen en el chip pero no llegan a ningún header: por eso son seis y no ocho. Los pines 18/19 y 20/21 están compartidos con `Serial1` e I²C (`SDA`/`SCL`).

## ej02 — [la primera ISR](ej02_isr_enciende/)

Tres cosas nuevas: `attachInterrupt( digitalPinToInterrupt(pin), funcion, RISING )`, la **ISR** (una función sin parámetros ni retorno **que nadie llama desde el código**), y el pin 21 en `INPUT` a secas, porque lo excita el pin 4 y no queda flotando.

Probar: a los 2 s el LED prende y queda prendido — **mientras el `loop()` está clavado en `delay(2000)`**. ¿En qué línea del programa se enciende? En ninguna que el `loop()` ejecute: la ISR la llama el hardware.

Qué hizo `attachInterrupt` por nosotros: guardó el puntero a tu función en una tabla, escribió el registro que elige el flanco (`EICRA`) y habilitó `INT0` en la máscara (`EIMSK`). La ISR «de verdad» es `ISR(INT0_vect)` y sólo llama a tu función por puntero. Entrar cuesta 5 ciclos como mínimo más el prólogo del compilador, porque el hardware **sólo apila el PC**.

## ej03 — [una cuadrada de 5 Hz y una ISR que invierte](ej03_isr_toggle_5hz/)

El generador pasa de un flanco único a una onda cuadrada escrita con `millis()`. Con `RISING`, la ISR entra 5 veces por segundo.

Probar: el LED parpadea a **2,5 Hz** (dos flancos ascendentes por ciclo). Después `FALLING` (mismo resultado, otro flanco) y `CHANGE` (10 por segundo → 5 Hz).

* **Orden adentro de la ISR:** primero invertir, después escribir. Al revés, el LED muestra el estado *anterior*.
* `ledState` **no** lleva `volatile`, a propósito: la lee y la escribe sólo la ISR. `volatile` es para lo que se **comparte** — eso viene en el ej04.
* ⛔ **No** probar el modo `LOW`: dispara *mientras* el pin esté bajo, la ISR reentra sin parar y el `loop()` no vuelve a correr.

## ej04 — [contar entradas y avisar cada 500 · sección crítica](ej04_isr_contador_serial/)

**La ISR no imprime: cuenta.** `contador++` y sale; imprime el `loop()`. `contador` es `volatile uint16_t`: la escribe la ISR, la lee el `loop()`. Primera variable **compartida**.

Probar: monitor serie, un aviso por segundo. El LED se ve a media luz (500 Hz es más rápido que el ojo).

* **La sección crítica.** `contador` son 2 bytes en un micro de 8 bits: el `loop()` los lee en dos instrucciones. Si la ISR se mete entre una y otra, la copia mezcla el byte bajo de una cuenta con el alto de otra: leo `0xFF`, entra la ISR (`0x01FF → 0x0200`), leo `0x02`, queda `0x02FF` — **256 de más**. `noInterrupts()` / `interrupts()` cierran la ventana.
* Sacarlos y volver a correr: en Wokwi probablemente **nunca** falle, porque la ventana son dos instrucciones. Es un bug **probabilístico**, y por eso es peor que uno que falla siempre.
* Es lo mismo que hace `millis()` por dentro: apaga las interrupciones, copia sus 4 bytes, restaura. Ya lo usaban la clase pasada.
* **`volatile` no hace atómica a la variable**, sólo obliga a leerla de memoria cada vez. Dos problemas distintos, dos soluciones distintas.
* `Serial.print()` adentro de una ISR no «falla»: manda el byte esperando al UART con las interrupciones apagadas. Funciona y **bloquea la ISR**. 25 caracteres a 115200 baud son ~2 ms; en una ISR es una eternidad.

## ej05 — [el ejercicio 5 de la clase pasada, con interrupción](ej05_boton_isr_parpadeo/)

*Encender al presionar. Parpadear al volver a presionar. Apagar al volver a presionar.* **Mismo enunciado que el [ejercicio 5 de la clase 14](../clase-14/ej5/)**, y la aplicación es idéntica línea por línea. Cambian seis líneas de `leerBoton()` y aparece la ISR.

Probar: se comporta **exactamente igual** que la versión por polling. Ése es el punto.

![El lector de botón con ISR](diagramas/mef-lector-con-isr.svg)

* **El rebote empeoró.** Con `CHANGE` la ISR dispara en cada rebote: simulado con 5 ms de rebote, **114 entradas a la ISR en tres pulsaciones** (~19 por flanco). La máquina de estados ve **3** eventos. La interrupción no filtró nada; filtró la MEF.
* **Y la MEF de la clase pasada es la única solución posible acá:** adentro de una ISR **no hay `delay()`**. `delay()` espera mirando el reloj, y ese reloj lo actualiza la interrupción del Timer 0, que no corre mientras estamos en otra ISR. `delay(40)` en una ISR **no termina nunca**.
* **Cómo se hablan la ISR y la máquina:** por una bandera de un byte, `volatile uint8_t hayFlanco`. La ISR la levanta y sale; el driver la consume en los estados de reposo y a los 40 ms **lee el pin para confirmar**. La ISR no guarda qué nivel vio, y no hace falta: en `buttonUp` el único flanco posible es una presión.
* `hayFlanco` es **un byte** — leerlo o escribirlo es atómico en el AVR. Por eso acá no hay `noInterrupts()` y en el ej04 sí.
* **Por qué `hayFlanco = 0` aparece en casi todos los `case`.** La bandera es un buzón de un solo casillero —«pasó algo en el pin que todavía no miré»—, y la máquina **lo vacía cada vez que lo mira**. El motivo cambia según el estado: en los de **reposo** el aviso *es* el evento, y consumirlo es borrarlo (si no, el mismo flanco dispara dos transiciones); en los de **espera**, a los 40 ms, lo que hay en el buzón son los rebotes de esos 40 ms, que ya no valen nada y se tiran. **El veredicto no lo da la bandera: lo da la lectura del pin.** La bandera dice «mirá», el pin dice «sí o no».
* **Por eso el orden es limpiar y después leer:** un flanco que caiga entre las dos líneas queda anotado para el próximo estado en vez de perderse. Al revés se puede perder un «soltar» rápido.
* **Si falta una de las cuatro, el programa igual anda** —cada camino termina en un `digitalRead()`, así que una bandera sucia sólo cuesta un viaje de 40 ms al pedo—, y por eso el error no se ve. Si faltan **todas**, la bandera queda en 1 para siempre y la espera deja de contarse desde el flanco: medido en simulación, el soltar se confirma a los **20 ms** del flanco en vez de a los 40. El antirrebote parece andar, con la mitad de ventana.
* `CHANGE` y no `FALLING`: hacen falta los dos flancos (con `FALLING` vería la presión pero nunca el soltar). Y `pinMode( buttonPin , INPUT_PULLUP )` va **antes** de `attachInterrupt`: si el pin flota un instante, la ISR dispara sola.
* **El experimento de la clase 14, otra vez:** `delay(200)` al final del `loop()`. La ISR ve los flancos, pero la máquina los procesa recién cuando el `loop()` vuelve. **La interrupción no arregla un `loop()` lento: arregla que el evento no se pierda.**

## Errores frecuentes

* `attachInterrupt` sobre un pin que no es de interrupción (8, 9, 13…) → **no hace nada, en silencio**.
* Escribir el número a mano (`attachInterrupt(0, …)`) → en el Mega el 0 es el pin **2**; el 21 es el **2**.
* `delay()` adentro de la ISR → se cuelga. `Serial.print()` adentro de la ISR → bloquea.
* Olvidarse `volatile` en la variable compartida → el compilador puede quedarse con el valor viejo.
* Creer que `volatile` alcanza para 2 o 4 bytes → hace falta la sección crítica.
* `LOW` como modo con un botón → la ISR reentra mientras esté apretado.
* `attachInterrupt` antes de `pinMode(..., INPUT_PULLUP)` → un disparo fantasma al arrancar.
* Poner la lógica en la ISR («total es corta») → la ISR crece, y con ella todo lo que no puede interrumpirla.
* Leer el pin y **después** limpiar la bandera → se puede perder un flanco. Limpiar primero.
