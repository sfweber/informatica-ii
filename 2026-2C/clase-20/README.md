# Clase 20

**Tema:** **Pilas y colas.** Dos estructuras que se definen por el orden en que salen los datos: la pila es LIFO (el último que entra es el primero que sale) y la cola es FIFO (el primero que entra es el primero que sale). Las dos se implementan sobre un vector de tamaño fijo creado en el heap.

## Cómo compilarlos

Todos son `src/` + `include/` + `Makefile` (el de la clase 16): `make` compila, `make run` compila y ejecuta, `make clean` borra. Si tocan un `.h`: `make clean && make`.

## Regla para los errores

Un método que no puede hacer lo que le piden (la pila está llena o vacía, la cola está llena o vacía) **avisa por `std::cerr` y vuelve**; si tiene que devolver un dato, devuelve `-1`. El `-1` es una convención: sirve mientras la estructura no guarde valores negativos.

## Pilas

* **[ej09](ej09_pila/)** — `class Pila` sobre un vector en el heap: el constructor recibe el tamaño máximo y hace `new int [tamMax]`; el destructor hace `delete []`. `m_top` es el índice de la cima: `-1` es la pila vacía. `push` incrementa `m_top` y guarda; `pop` lee y decrementa; `getTop` lee sin sacar; `isEmpty` e `isFull` comparan `m_top` con `-1` y con `tamMax - 1`. Esta versión **no controla** llena ni vacía: `push` sobre una pila llena escribe fuera del vector y `pop` sobre una vacía lee `m_datoPila[-1]`.
* **[ej10](ej10_pila_segura/)** — La misma `Pila` con los controles: `push` pregunta `isFull ()` y `pop` pregunta `isEmpty ()`; si no pueden, avisan por `cerr`. Se agrega `borrarPila`: `m_top = -1` (los datos quedan en el vector, pero ya no son parte de la pila). El `main` mete cuatro en una pila de tres y saca cuatro: el cuarto `push` y el cuarto `pop` avisan.

## Colas

* **[ej11](ej11_cola_circular/)** — `class CircQueue`: cola circular sobre un vector en el heap. `m_front` es el índice del primero, `m_rear` el del último y `m_count` la cantidad de elementos. `enqueue` avanza `m_rear` con `(m_rear + 1) % m_tamMax`: al llegar al final del vector vuelve al índice 0, por eso la cola es circular. `dequeue` lee en `m_front` y lo avanza con el mismo `%`; si saca el único elemento, vuelve a la condición inicial (`m_front = 0`, `m_rear = -1`). `isEmpty` e `isFull` comparan `m_count` con `0` y con `m_tamMax`. El `main` llena la cola de cinco, saca tres, mete dos más (que dan la vuelta) y vacía: salen en el orden en que entraron.

## Errores frecuentes

* Olvidar los controles de llena y vacía: no da error de compilación, escribe o lee fuera del vector y el programa se comporta mal en otro lado.
* En la pila, incrementar `m_top` **después** de guardar: pisa la cima anterior.
* En la cola, avanzar `m_rear` o `m_front` sin el `%`: el índice se pasa del final del vector.
* Distinguir llena de vacía solo con `m_front` y `m_rear`: cuando la cola da la vuelta, los dos casos se ven iguales. Por eso está `m_count`.
* Usar `getTop` o `getFront` sobre una estructura vacía: devuelven lo que haya en esa posición del vector, no avisan.
