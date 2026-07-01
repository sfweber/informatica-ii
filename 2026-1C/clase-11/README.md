# Clase 11

**Tema:** Máquinas de estado (FSM). Modelar un sistema con **estados** finitos, **transiciones** y **acciones**, e implementarlo en C. Dos formas: con `switch`-`case` + `enum`, y con **punteros a función** (un estado = una función). De un reconocedor simple a una **FSM extendida (EFSM)** que agrega variables cuando la máquina sola no alcanza.

## Ejemplos

* **ejemplo1.c** — Contador **par / impar** (máquina de **Moore**: la salida depende solo del estado).
  Probar: `gcc -Wall ejemplo1.c -o ejemplo1 && echo "101" | ./ejemplo1`

* **ejemplo2.c** — Detector de la secuencia **"abcd"** con `switch`-`case` (**Mealy**).
  Probar: `gcc -Wall ejemplo2.c -o ejemplo2 && echo "abcd" | ./ejemplo2` → la detecta.
  ⚠️ **Tiene la TAREA de abajo.**

* **ejemplo2_punteros.c** — El **mismo** detector "abcd" pero con **punteros a función**. Versión **correcta**.
  Probar: `gcc -Wall ejemplo2_punteros.c -o ejemplo2_punteros && echo "ababcd" | ./ejemplo2_punteros` → la detecta.

* **ejemplo3.c** — El detector "abcd" **extendido** con un contador (**EFSM**): cuenta cuántas veces aparece.
  La máquina (4 estados) no cambia; se agrega **una variable**. Probar: `echo "abcdxabcd" | ./ejemplo3` → 2 detecciones.

* **ejemplo4.c** — Tratamiento de un **protocolo** de comunicaciones `| STX | CANT | DATOS | CHK | ETX |` con checksum XOR (**EFSM**). Probar: `gcc -Wall ejemplo4.c -o ejemplo4 && ./ejemplo4`.

* **formato_FSM.c** / **formato_FSM_ptr.c** — **Plantillas** (moldes) de FSM: con `switch`+`enum` y con punteros a función. Son esqueletos para completar (definís vos los estados y la condición de salida).

* **enum1.c** / **enum2.c** — Demos de `enum` (prerequisito): constantes simbólicas y sus valores enteros.

> Los programas leen del teclado y terminan con **EOF**: `Ctrl+D` (Linux) / `Ctrl+Z`+Enter (Windows), o pipeando la entrada (`echo "abcd" | ./prog`).
>
> El **Ejemplo 5** (anti-rebote de un pulsador — *timed FSM*) se ve en las slides; no tiene código en el repo.

## TAREA

`ejemplo2.c` detecta `"abcd"`, pero **falla** cuando la secuencia aparece **después de un comienzo parcial**. Por ejemplo, con la entrada **`ababcd`** la secuencia `abcd` está adentro (posiciones 3 a 6), pero el programa **no la detecta**:

```
echo "ababcd" | ./ejemplo2      # no detecta (mal)
echo "ababcd" | ./ejemplo2_punteros   # sí detecta (así debería)
```

**Corregí la máquina de estados de `ejemplo2.c` (con `switch`-`case`) para que la detecte igual.**

* Pista: pensá qué debería pasar con una **`a`** cuando ya venías avanzando en la secuencia (estás en un estado intermedio y llega otra `a`). ¿A qué estado conviene ir?
* Podés comparar el comportamiento con `ejemplo2_punteros.c`, que ya lo resuelve.
* Entregá `ejemplo2.c` corregido, manteniendo la estructura con `switch`-`case`.
