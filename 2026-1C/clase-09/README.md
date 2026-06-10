# Clase 09

**Tema:** Punteros a función — guardar la dirección de una función en una variable para invocarla a través de ella: declaración e invocación, tablas de función (*dispatch tables*), callbacks (pasar funciones como argumento) y simulación de métodos con `struct`.

## Ejemplos

**Tema:** Declaración e invocación

* **ptr_fun1.c** — Puntero a `suma` declarado con la lista de argumentos vacía `()`; se invoca explícito con `(*p)(x,y)`.
  Probar: compilar con `gcc -Wall -Wextra -Wstrict-prototypes ptr_fun1.c -o ptr` y ver el warning por declarar `()` sin tipos.

* **ptr_fun2.c** — Igual, pero con la lista de argumentos completa `(int, int)` en la declaración.
  Probar: compilar con los mismos flags y comprobar que el warning desaparece.

* **ptr_fun3.c** — Agrega un puntero a `printf` declarado con `()`, sin su firma real.
  Probar: compilar con `-Wall -Wextra` y ver el warning por la firma incompatible de `printf`.

* **ptr_fun4.c** — Soluciona el warning: declara el puntero con la firma real de `printf` (`const char*, ...`) y lo usa para imprimir.
  Probar: compilar limpio y verificar que imprime a través del puntero `mirar`.

* **ptr_fun5.c** — Usa `typedef` (`opBinaria`, `opUnaria`) para nombrar los tipos de puntero a función.
  Probar: comparar la legibilidad con ptr_fun1. Agregar otra función y declararla con el typedef.

**Tema:** Tabla de funciones (vector de punteros)

* **vptr1.c** — Vector de punteros a función elegido por un índice que ingresa el usuario (suma/resta/producto/división/resto), **sin** validar el índice.
  Probar: ejecutar con una opción válida (0-4) y después con una fuera de rango (ej. 7) y ver el comportamiento indefinido.

* **vptr2.c** — Igual que vptr1 pero valida que el índice esté en rango antes de invocar.
  Probar: repetir la opción fuera de rango y ver que ahora avisa "Selección incorrecta".

* **vptr3.c** — Recorre toda la tabla con un `for`; el tamaño se fija con `#define NUM_FUNCS`.
  Probar: ejecutar y ver las 5 operaciones. Agregar una función a la tabla (prototipo + array + `NUM_FUNCS`) y ver que el `for` la toma sola.

**Tema:** Callbacks (funciones como argumento)

* **callback1.c** — Función genérica `aplicar(cmp, x, y)` que recibe una función (`max` o `min`) por parámetro y la invoca.
  Probar: ejecutar y notar que `aplicar` no cambia; el comportamiento lo define la función que se le pasa.

* **suma_2_3.c** — Combina tabla + callback: elige una función unaria (`cuadrado`/`cubo`) de una tabla y se la pasa a `suma`, que la aplica a dos valores y suma los resultados.
  Probar: ejecutar con cada opción (0, 1) y verificar `pf(x) + pf(y)`.

**Tema:** Punteros a función en estructuras (simulación de métodos)

* **metodo_en_c.c** — Puntero a función dentro de un `struct Figura`, usado como si fuera un método: `figura.area(&figura)`.
  Probar: ejecutar y ver el área de rectángulo y círculo. Notar que cada figura apunta a su propia función de área.

## Extra — opcional (no se dicta este año)

Aplicación de los punteros a función al cálculo numérico: se pasa `f(x)` por puntero a un método genérico (Regula Falsi) que busca el cruce por cero. Queda como material de lectura.

* **iterativo.c** — Regula Falsi iterativo: `rf` recibe `f(x)` por puntero y busca la raíz en `[a, b]` con tope de iteraciones y control de convergencia (`<math.h>`).
  Probar: compilar con `-lm` y ejecutar (función `x³−10x²+31x−40` en `[0, 7]`); dar Enter para ver cada aproximación.

* **regula_falsi.c** — La misma idea pero **recursiva**.
  Probar: compilar con `-lm`, comparar con iterativo.c y ver qué pasa si el intervalo no encierra una raíz.

* **regula_falsi_con_interv.c** — Agrega `buscar_intervalo`, que también recibe `f(x)` por puntero y barre un rango buscando un cambio de signo para fijar `[a, b]` solo.
  Probar: compilar con `-lm` y ver primero el intervalo detectado y después el cruce por cero.
