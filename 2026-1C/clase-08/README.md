# Clase 08

**Tema:** Recursividad — una función que se llama a sí misma para resolver un problema describiéndolo en términos de una versión más chica de sí mismo. Las dos reglas que la hacen terminar (**caso base** + cada llamada **se acerca al caso base**), cómo se ve en el stack, y el patrón de **divide y vencerás**.

## Ejemplos

**Tema:** La idea de recursión

* **recursion_basica.c** — El ejemplo mínimo para ver el mecanismo: una función `fr(i)` que se imprime a sí misma y se vuelve a llamar con `i + 1` hasta llegar a `i == 6` (el caso base, donde corta). No hace ninguna cuenta útil; sirve solo para *ver* cómo se apilan las llamadas al bajar y cómo se devuelve el valor al desarmarse la pila.
  Probar: compilar con `gcc -Wall recursion_basica.c -o recursion_basica` y ejecutar. Notar que imprime `i=3, 4, 5` (al **bajar**, antes de cada llamada) y que el resultado final `i=6` es el valor que devuelve el caso base y que va volviendo por la pila. Cambiar el `fr(3)` del `main` por otro número, o el `i != 6` del caso base, y predecir la salida. Para ver el peligro: comentar el `if` (sacar el caso base) y ejecutar → la recursión nunca termina y revienta el stack (*segmentation fault* / *stack overflow*).

**Tema:** Ejemplos clásicos

* **factorial.c** — Factorial recursivo: `n! = n * (n-1)!`, con caso base `0! = 1`. La traducción directa de la definición matemática a código.
  Probar: compilar con `gcc -Wall factorial.c -o factorial` y ejecutar (calcula `5! = 120`). Cambiar `numero` en el `main`. Probar con `n = 13` o más y ver que el resultado se rompe: `int` no alcanza para factoriales grandes (desborda). Pensar cuántas llamadas recursivas hace para un `n` dado.

* **fibonacci.c** — Fibonacci recursivo: `F(n) = F(n-1) + F(n-2)`, con **dos** casos base (`F(0)=0`, `F(1)=1`). Es recursión *múltiple* (la función se llama dos veces), y por eso es **exponencial**: recalcula los mismos términos una y otra vez.
  Probar: compilar y ejecutar con un `n` chico (`10` → `55`). Después probar con `n = 40` o `45` y notar que **tarda muchísimo** (segundos o más): esa lentitud es el árbol de llamadas duplicadas. Dibujar el árbol de `F(5)` para ver cuántas veces se calcula `F(2)`.

* **fibonacci_iterativo.c** — El mismo Fibonacci, pero con un `for` y dos variables que se van pisando. Resuelve el problema en tiempo **lineal**, sin recursión. Imprime los primeros 46 términos en columnas.
  Probar: compilar y ejecutar — la tabla sale **instantánea**. Compararlo con `fibonacci.c`: medir con `time ./fibonacci` (n=40) vs lo que tarda la tabla entera acá. Conclusión: la recursión es más *legible* pero no siempre más *eficiente*; hay que saber elegir.

**Tema:** Divide y vencerás

* **hanoi.c** — Torres de Hanoi: mover `n` discos de una torre a otra usando una auxiliar, sin poner nunca un disco grande sobre uno chico. El truco recursivo: mover `n-1` discos al auxiliar, mover el disco grande al destino, y mover los `n-1` del auxiliar al destino. Imposible de pensar con un `for`, casi trivial con recursión.
  Probar: compilar con `gcc -Wall hanoi.c -o hanoi` y ejecutar con `n = 4` (imprime la secuencia de movimientos). Contar los movimientos: son `2^n - 1` (para 4 discos, 15). Cambiar `n` a 3, 5, 6 y verificar que la cantidad de movimientos sigue `2^n - 1` — por eso el problema "explota" con pocos discos más.

* **busquedabin.c** — Búsqueda binaria recursiva sobre un arreglo **ordenado**: mirar el elemento del medio; si es el buscado, listo; si el objetivo es menor, buscar recursivamente en la mitad izquierda; si es mayor, en la derecha. Tiene **dos casos base**: encontrarlo (`vec[medio] == objetivo`) o agotar el rango (`izquierda > derecha`).
  Probar: compilar y ejecutar tal cual (busca el `8`, que **no** está → "no encontrado"). Cambiar `objetivo` por un valor que sí esté (ej. `7` → posición 3) y por los extremos (`1` y `13`). Agregar un `printf` adentro de la función para ver en qué `medio` mira en cada paso y comprobar que descarta la mitad del arreglo cada vez.

**Tema:** El orden importa — operar antes o después de la llamada

* **dec2bin.c** — Convierte un decimal a binario con recursión. La clave está en el **orden**: primero la llamada recursiva `dec2bin(n/2)` y *después* el `printf("%d", n%2)`. Como los `printf` quedan pendientes en la pila y se ejecutan al volver, los bits salen en el orden correcto (del más significativo al menos).
  Probar: compilar y ejecutar (`251` → `11111011`). Cambiar `n`. Para entender por qué funciona: **invertir** las dos líneas (poner el `printf` *antes* de la llamada) y ver que el binario sale al revés. El caso base es `n == 0`: corta sin imprimir nada.
