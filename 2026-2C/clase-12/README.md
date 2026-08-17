# Clase 12

**Tema:** Representación de números reales. Cómo se guardan los números con coma en una cantidad **finita** de bits: **punto fijo** (BSS/SM: rango, resolución, error de truncar vs redondear) y **punto flotante IEEE 754** (mantisa normalizada, bit implícito, exponente en exceso, denormales, ∞ y NaN). Qué precisión tienen de verdad `float` y `double` (los "6 a 9" y "15 a 17" dígitos), por qué `0.1` no existe exacto, y qué pasa cuando eso se ignora.

## Ejemplos

* **ejemplo01-tipos.c** — Tamaño (`sizeof`) y rango de los tipos **enteros** de C (`<limits.h>`), el punto de partida: con N bits solo hay 2^N valores posibles. Son las tablas de la presentación 12.1.
  Probar: `gcc -Wall ejemplo01-tipos.c -o ejemplo01-tipos && ./ejemplo01-tipos`

* **ejemplo02-union.c** — El "Ejemplo01 – Profesor Argibay" de la presentación 12.3: una **unión** de `unsigned char [4]` con un `float` para espiar los bytes de un flotante en memoria. Primero carga el patrón `0x5F3759DF` byte a byte y muestra qué float resulta; después al revés: ingresás un flotante y ves sus bytes en los dos órdenes (**hexadecimal** vs **memoria little-endian**).
  Probar: `gcc -Wall ejemplo02-union.c -o ejemplo02-union && ./ejemplo02-union` → ¿de qué juego famoso salió ese patrón de bits? (está en la 12.3)

* **intfloat.c** — *(extra: no está en las slides, lo agregamos como evidencia)* Un `for` que hace `int → float → int` alrededor de 16777216 (= 2²⁴) y marca `SE PERDIO` cuando el número que vuelve no es el que entró. Muestra que `float` **no puede representar todos los enteros**: su mantisa tiene 23+1 bits, así que a partir de 2²⁴ los enteros impares no existen como `float`.
  Probar: `gcc -Wall intfloat.c -o intfloat && ./intfloat` → ¿por qué se pierden justo los impares? ¿Qué pasaría con `double`?

## Visualizador — el plano float

Demo que se usa en clase (presentación 12.1, "Visualizador - Epsilon"): dibuja en la terminal una ventana fija de 8×8 unidades del "plano float" y la va corriendo por la diagonal. Cerca del origen los floats forman una grilla tan densa que se ve maciza; a medida que te alejás, la grilla se ralea, y en 2²⁷ queda **un solo float** en toda la ventana. También muestra en vivo cómo `x = x + 0.1f;` deja de avanzar cuando el paso entre floats se hace más grande que 0.1.

> ⚠️ **El código NO es material de estudio.** Está acá solo para que puedan **correr la demo y ver el resultado** — usa cosas que exceden la materia (control de terminal, `nextafterf`, manipulación de bits). No hace falta leerlo ni entenderlo.

* **Compilar (solo Linux / WSL):** `gcc -O2 -std=c11 -Wall -o epsviz visualizador-epsilon.c -lm`
  No compila en Windows/MinGW (usa la terminal de Linux). Si están en Windows, usen WSL.
* **Usar:** flechas o `WASD` para saltar al float vecino, `+`/`-` para alejarse/acercarse al origen, `m` para ejecutar `x = x + 0.1f;` y ver a qué float redondea, `u` salta directo a 2²⁴, `1` vuelve al origen, `q` sale.
