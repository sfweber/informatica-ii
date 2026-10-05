# Clase 17

**Tema:** **Memoria dinámica en C++ y destructores.** `new`/`delete` y `new[]`/`delete[]` en lugar de `malloc`/`free`, los mismos errores que en C (puntero colgante, fuga, doble liberación) ahora con `new`, y la parte central: el **destructor**, la función miembro que corre sola cuando el objeto muere. Cierra con la clase `miVector`, que pide su memoria en el constructor y la libera en el destructor.

## Cómo compilarlos

* **Un solo archivo** (`ej01` a `ej15`): `g++ -Wall -Wextra -std=c++17 main.cpp -o programa && ./programa`.
* **`ej17`** (`src/` + `include/` + `Makefile`): `make` compila, `make run` compila y ejecuta, `make clean` borra. Mismo Makefile que la clase 16. Si tocan el `.h`: `make clean && make`.
* Para ver fugas y accesos inválidos: `valgrind ./programa` (lo usaron en recursividad) o compilar con `g++ -g -fsanitize=address main.cpp -o programa`.

## new / delete

* **[ej01](ej01_stack_overflow/)** — **Crashea a propósito.** `int vec[3000000]` son 12 MB en la pila, que en Linux es de 8 MB: `Segmentation fault`. Con `1000000` (4 MB) no crashea. El vector se usa (`vec[0] = 1`) porque si no el compilador lo elimina.
* **[ej02](ej02_new_int/)** — `new int`: reserva un `int` en el heap, sin inicializar. `new` recibe un **tipo** (no bytes: no hace falta `sizeof`) y devuelve un puntero **a ese tipo** (no hace falta castear, como con `malloc`). Si falla no devuelve `NULL`: lanza `std::bad_alloc`.
* **[ej03](ej03_new_inicializacion_directa/)** — `new int (5)`, inicialización directa.
* **[ej04](ej04_new_inicializacion_uniforme/)** — `new int {5}`, inicialización uniforme. Los tres hacen `delete`.
* **[ej05](ej05_delete_puntero_colgante/)** — imprime `*ptr` **después** del `delete`. `delete` no borra nada: devuelve el bloque al programa, y `ptr` sigue apuntando ahí (puntero colgante). Leerlo es **comportamiento indefinido**: puede salir el `5`, basura o caerse.
* **[ej06](ej06_delete_mas_nullptr/)** — **Crashea a propósito.** Lo mismo con `ptr = nullptr` después del `delete`: el error pasa de silencioso a `Segmentation fault`.
* **[ej07](ej07_puntero_nulo/)** — `int *ptr {nullptr}` y `if (!ptr)` antes del `new`. `nullptr` reemplaza al `NULL` de C.
* **[ej08](ej08_leak_en_funcion/)** — el `new` está en `asignar()` y `ptr` muere al cerrar la llave: nadie puede hacer `delete`. **Memory leak.**
* **[ej09](ej09_leak_puntero_reasignado/)** — `ptr = &i;` después del `new`: el bloque queda huérfano. Y si ahora alguien hace `delete ptr`, libera memoria de la **pila**.
* **[ej10](ej10_leak_new_dos_veces/)** — dos `new` sobre el mismo puntero, un solo `delete`: el primer bloque se pierde.
* **[ej11](ej11_new_delete_vector/)** — `new int[x]` / `delete[] ptr`: el tamaño se decide en tiempo de ejecución. **`new[]` se libera con `delete[]`**, nunca con `delete` ni con `free`. Con `x` negativo, `new[]` aborta: por eso el `if (x <= 0)`.
* **[ej12](ej12_vector_inicializado_cero/)** — `new int[x] {}`: todos en cero. Ojo: `{5}` pone **solo el primero** en 5.
* **[ej13](ej13_vector_decae_en_puntero/)** — `triplicar (int *, int)`: adentro de la función `sizeof (vec)` es el tamaño de un puntero. El tamaño hay que pasarlo aparte… o guardarlo adentro de un objeto, que es lo que hace `miVector`.

## Destructores

Mismo nombre que la clase con `~` adelante, sin parámetros ni tipo de retorno, uno solo por clase. Se llama solo cuando el objeto sale de su ámbito, o con `delete` si se creó con `new`. Si no lo escriben, el compilador genera uno que no hace nada.

* **[ej14](ej14_destructor/)** — constructor y destructor que solo imprimen. `obj1` nace y muere dentro de `crearObjeto()`: la segunda línea aparece al cerrar esa llave, no al final del `main`.
* **[ej15](ej15_destructor_libera_memoria/)** — `new int[20]` en el constructor, `delete[]` en el destructor. El primer destructor que hace algo: el objeto pide su memoria al nacer y la devuelve al morir, sin que el `main` tenga que acordarse.
* **[ej16](ej16_malloc_vs_new/)** — la misma clase pedida con `malloc`/`free` y con `new`/`delete`. Con `malloc` no se imprime nada: hay bytes, pero el objeto **nunca nació** (no corrió el constructor) y `free` tampoco llama al destructor. Es la razón para usar `new`/`delete` en C++.
* **[ej17](ej17_mivector/)** — `class miVector`: un vector de enteros cuyo tamaño se elige al crear el objeto (`miVector obj1 (tam)`). El constructor hace el `new[]` y guarda el tamaño; el destructor hace el `delete[]`; `setValor`/`getValor` rechazan posiciones fuera de `0 .. tam-1`.
  Si el tamaño no es válido, el constructor hace `exit(0)`: un constructor **no devuelve nada**, así que no tiene forma de avisar que falló. El `main` crea `obj2 (-1)` a propósito para verlo: el programa termina ahí, **sin ejecutar el destructor de `obj1`**. Comentar esa línea para ver el resto.

## Errores frecuentes

* `delete` sobre lo que se pidió con `new[]` (o `free` sobre lo que se pidió con `new`): compila, y es comportamiento indefinido. Las parejas son `new`/`delete`, `new[]`/`delete[]`, `malloc`/`free`.
* Usar un puntero después del `delete` (`ej05`). Ponerlo en `nullptr` no arregla el bug, pero lo hace visible (`ej06`).
* Perder el único puntero a un bloque (`ej08`, `ej09`, `ej10`): no hay forma de liberarlo. Ni g++ ni el programa avisan; valgrind o `-fsanitize=address` sí.
* `new int[x] {5}` esperando un vector lleno de 5: solo el primero.
* `return` sin valor en una función que devuelve algo (`control reaches end of non-void function`): el que llamó recibe basura. Todos los caminos tienen que terminar en `return`.
* `pos <= m_tam` como control de rango: deja pasar `pos == m_tam`, que está fuera del vector.
