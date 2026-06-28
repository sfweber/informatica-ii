# Clase 10

**Tema:** Métodos de ordenamiento. De los básicos O(n²) a los avanzados (Shell, quicksort) y `qsort` de la biblioteca estándar, que ordena cualquier tipo recibiendo el criterio por puntero a función.

## Ejemplos

**Tema:** Métodos básicos O(n²)

* **intercambio.c** — Compara `vec[i]` con cada elemento posterior y los intercambia si están desordenados.
  Probar: `gcc -Wall intercambio.c -o intercambio && ./intercambio` y ver el vector ordenado.

* **seleccion.c** — En cada pasada busca el menor del resto y lo lleva a la posición `i` (un solo intercambio por pasada).
  Probar: compilar igual y comparar la cantidad de intercambios con burbujeo.

* **insercion.c** — Toma cada elemento y lo inserta en su lugar **desplazando** hacia la derecha los mayores (`aux`).
  Probar: compilar y seguir cómo se desplaza cada valor hasta su posición.

* **burbujeo.c** — Compara elementos **adyacentes** y los intercambia, repitiendo pasadas hasta ordenar.
  Probar: compilar y notar que solo mira vecinos, a diferencia de intercambio.

**Tema:** Métodos avanzados

* **shell.c** — Shell sort: la misma inserción pero con **saltos** (`paso = n/2` que se reduce a la mitad en cada vuelta).
  Probar: compilar y ver cómo con saltos grandes acomoda rápido los valores lejanos.

* **quick.c** — Quicksort recursivo con pivote central: particiona y ordena cada mitad.
  Probar: compilar y seguir la recursión sobre las sublistas izquierda y derecha.

**Tema:** qsort de la biblioteca estándar

* **qsort_stdlib1.c** — `qsort` sobre enteros, ascendente y descendente con dos comparadores. Usa la forma segura `(x>y)-(x<y)`.
  Probar: compilar y ver las dos salidas; invertir el comparador y comprobar el orden.

* **qsort_stdlib2.c** — `qsort` sobre un arreglo de `struct`, ordenado por un campo (la edad).
  Probar: compilar y cambiar el comparador para ordenar por otro campo.

* **qsort_stdlib3.c** — `qsort` sobre un arreglo de cadenas: doble desreferencia (`char**`) y `strcmp`.
  Probar: compilar y verificar el orden alfabético.

**Tema:** Comparación de rendimiento

* **comparaciones.c** — Cronometra burbuja, selección y quicksort sobre el mismo vector (`clock()`, n=20000).
  Probar: compilar y ver la diferencia de tiempos entre los O(n²) y quicksort.

* **comp_rendimientos.c** — Quicksort propio vs `qsort` de la biblioteca con n grande: muestra el costo de la indirección del comparador por puntero a función.
  Probar: compilar y ejecutar (tarda); comparar ambos tiempos.

## Visualizador interactivo

Dashboard web para ver los algoritmos **paso a paso** con el código al lado, predicción, complejidad y un gráfico de operaciones vs n.

* **En vivo:** https://sfweber.github.io/informatica-ii/2026-1C/clase-10/visualizador-ordenamiento/
* **Offline:** abrir `visualizador-ordenamiento/index.html` (doble clic; no necesita internet).
