# Clase 18

**Tema:** **Listas simplemente enlazadas (parte 1).** La primera estructura de datos dinámica: nodos en el heap encadenados por punteros.

## Cómo compilarlos

Todos son `src/` + `include/` + `Makefile` (el de la clase 16): `make` compila, `make run` compila y ejecuta, `make clean` borra. Si tocan un `.h`: `make clean && make`.

## Listas simplemente enlazadas

Cada paso agrega algo al anterior. Los que leen de teclado terminan el ingreso con `-1`. La numeración arranca en `ej02`: sigue la del material de clase.

* **[ej02](ej02_lista_vacia/)** — `class Nodo` (un dato y un puntero al siguiente) y `class Lista` con un solo atributo: `Nodo* m_inicio`. En `nullptr`, la lista está vacía.
* **[ej03](ej03_crear_lista/)** — `crearLista ()`: cada valor ingresado crea un nodo **al comienzo** con `m_inicio = new Nodo (x, m_inicio)`. Todavía no se puede ver la lista ni se libera la memoria.
* **[ej04](ej04_recorrer/)** — `recorrerLista ()`: un `for` que arranca en `m_inicio`, avanza con `getSig ()` y termina en `nullptr`. `m_sig` y `m_dato` son privados: por eso los getters de `Nodo`. Los valores salen en orden inverso al de ingreso.
* **[ej05](ej05_destructor/)** — `~Lista ()`: libera nodo por nodo. Hay que guardar `p->getSig ()` **antes** del `delete p`.
* **[ej06](ej06_insertar_primero/)** — `insertarPrimero ()` en tres pasos: crear el nodo, hacer que apunte al primero (`setSig`), y que `m_inicio` apunte al nuevo. Hace lo mismo que la línea de `crearLista`, de a un nodo.
* **[ej07](ej07_insertar_ultimo/)** — `getUltimo ()` recorre hasta el último nodo y devuelve su dirección, o `nullptr` si la lista está vacía. `insertarUltimo ()` lo usa para enganchar el nodo nuevo; si la lista está vacía, llama a `insertarPrimero`.

## Errores frecuentes

* Perder `m_inicio`: es el único puntero a la lista. Por eso `crearLista ()` se llama una sola vez, sobre la lista recién creada.
* Leer `p->getSig ()` después de `delete p`: `p` ya es un puntero colgante.
* Usar el puntero que devuelve `getUltimo ()` sin verificar que no sea `nullptr`.
* Un nodo se libera con `delete`, sin corchetes: es un objeto, no un vector.

## Trabajo práctico

TP Matriz, parte 1: el enunciado está en la organización de GitHub de la materia.
