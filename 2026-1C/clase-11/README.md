# Clase 11

**Tema:** Máquinas de estado (FSM). Modelar un sistema con **estados** finitos, **transiciones** y **acciones**, e implementarlo en C con `switch`-`case` + `enum` (un estado por `case`). De un reconocedor simple a una **FSM extendida (EFSM)** que agrega variables cuando la máquina sola no alcanza.

## Ejemplos

* **ejemplo1.c** — Contador **par / impar** (máquina de **Moore**: la salida depende solo del estado).
  Probar: `gcc -Wall ejemplo1.c -o ejemplo1 && echo "101" | ./ejemplo1`

* **ejemplo2.c** — Detector de la secuencia **"abcd"** con `switch`-`case` (**Mealy**).
  Probar: `gcc -Wall ejemplo2.c -o ejemplo2 && echo "abcd" | ./ejemplo2` → la detecta.
  ⚠️ **Tiene la TAREA de abajo.**

* **ejemplo4.c** — Tratamiento de un **protocolo** de comunicaciones `| STX | CANT | DATOS | CHK | ETX |` con checksum XOR (**EFSM**). Probar: `gcc -Wall ejemplo4.c -o ejemplo4 && ./ejemplo4`.
  Tiene un **visualizador interactivo** (ver más abajo).

* **formato_FSM.c** — **Plantilla** (molde) de FSM con `switch`+`enum`. Es un esqueleto para completar (definís vos los estados y la condición de salida).

* **enum1.c** / **enum2.c** — Demos de `enum` (prerequisito): constantes simbólicas y sus valores enteros.

> Los programas leen del teclado y terminan con **EOF**: `Ctrl+D` (Linux) / `Ctrl+Z`+Enter (Windows), o pipeando la entrada (`echo "abcd" | ./prog`).

## Visualizador interactivo

Diagrama de la máquina de estados del protocolo (`ejemplo4.c`) **paso a paso**, con el código al lado.

* **En vivo:** https://sfweber.github.io/informatica-ii/2026-1C/clase-11/visualizador-protocolo/
* **Offline:** abrir `visualizador-protocolo/index.html` (doble clic; no necesita internet).

## TAREA

### Tarea 1 — corregir el detector "abcd"

`ejemplo2.c` detecta `"abcd"`, pero **falla** cuando la secuencia aparece **después de un comienzo parcial**. Por ejemplo, con la entrada **`ababcd`** la secuencia `abcd` está adentro (posiciones 3 a 6), pero el programa **no la detecta**:

```
echo "abcd"   | ./ejemplo2      # sí la detecta
echo "ababcd" | ./ejemplo2      # NO la detecta (mal) ← esto hay que corregir
```

**Corregí la máquina de estados de `ejemplo2.c` (con `switch`-`case`) para que la detecte igual.**

* Pista: pensá qué debería pasar con una **`a`** cuando ya venías avanzando en la secuencia (estás en un estado intermedio y llega otra `a`). ¿A qué estado conviene ir?
* Entregá `ejemplo2.c` corregido, manteniendo la estructura con `switch`-`case`.

### Tarea 2 — contar las apariciones (EFSM)

Partiendo de **tu** detector ya corregido (Tarea 1), extendelo para que **cuente cuántas veces aparece `abcd`** en la entrada. A la **tercera** aparición debe imprimir `ALARMA ACTIVA` y **reiniciar el conteo** (vuelve a cero y sigue contando).

Los cuatro estados **no cambian**: alcanza con agregar **una variable** (un contador). Una FSM + una variable de datos = **EFSM** (*extended FSM*).

* La acción `contador++` va en la **transición que completa `abcd`** (la que dispara la detección), no dentro de un estado.
* Pensá dónde declarás e inicializás el contador, y cómo lo reiniciás al llegar a 3.
* Probar (ejemplo): `echo "abcdabcdabcd" | ./tu_programa` → en la 3ª aparición imprime `ALARMA ACTIVA`.
* No hay solución en el repo **a propósito**: depende de cómo hayas armado tu máquina en la Tarea 1. Entregá tu `.c`.
