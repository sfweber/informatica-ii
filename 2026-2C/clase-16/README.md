# Clase 16

**Tema:** **Introducción a C++.** Flujos (`cout`/`cin`), programas en varios archivos y header guards, `namespace std`, y la parte central: **clases** (`private`/`public`, métodos, encapsulamiento) y **constructores** (predeterminado, por parámetros, con valores por defecto). Cierra con el botón de la clase 14 convertido en `class Boton`.

## Cómo compilarlos

* **Un solo archivo** (`ej01`, `ej02`, `ej03`, `ej07`): `g++ -Wall -Wextra -std=c++17 main.cpp -o programa && ./programa`. El `ej01` es C: va con `gcc`.
* **Varios archivos** (`src/` + `include/` + `Makefile`): `make` compila, `make run` compila y ejecuta, `make clean` borra. Es el Makefile del TP1 con `CXX`/`CXXFLAGS`, `g++`, `-std=c++17` y `-Iinclude`. Si tocan un `.h`: `make clean && make` (el Makefile no sigue los headers).
* **`ej12`** son proyectos de Wokwi (`sketch.ino` + `diagram.json`), Arduino Mega, mismo circuito que la clase 14 en `v6`: botón del **pin 21 a GND** sin resistencia (`INPUT_PULLUP`), LED en el **9** con 1 kΩ. `v2` agrega el botón del **pin 20** y un LED en el **10**.

## Flujos

* **[ej01](ej01_rectangulo_c/)** — Área de un rectángulo en C, tres funciones. Es el punto de partida de la clase: las variables y las funciones que las usan no tienen ninguna relación que el compilador conozca.
* **[ej02](ej02_flujos_cin_cout/)** — `std::cout <<` y `std::cin >>`. Compilarlo primero con `gcc`: **compila, pero no linkea** (`undefined reference to 'std::cout'`). `gcc` reconoce el `.cpp` y usa el compilador de C++, pero linkea con la biblioteca de C. `g++` es el mismo driver con la biblioteca de C++.
* **[ej03](ej03_flujos_hex_oct/)** — `std::hex` y `std::oct`. Con `255`, sale `ff` y `377`. Los manipuladores **quedan activos**: el `10` del final imprime `12`.

## Varios archivos y header guards

* **[ej04](ej04_multiples_archivos/)** — `producto()` en su propio `.cpp` con su `.h`. El compilador ve **un archivo por vez**: sin el prototipo, error de compilación; sin el `.cpp` en el linkeo, `undefined reference`. `#include "..."` busca en la carpeta del proyecto (`-Iinclude`); `<...>` en las del sistema.
* **[ej05](ej05_sin_header_guards/)** — ❌ **No compila, a propósito.** `producto.h` incluye `suma.h` y `suma.h` incluye `producto.h`:
  ```
  error: #include nested depth 200 exceeds maximum of 200
  ```
* **[ej06](ej06_con_header_guards/)** — Lo mismo con `#ifndef` / `#define` / `#endif` en cada `.h`. Es la **única** diferencia con `ej05`.

## Clases

* **[ej07](ej07_clase_fecha/)** — `class claseFecha` en un solo archivo. Los atributos son **privados por default** (`c1.dia = 78` no compila); `setFecha()` es la única puerta, y valida. El `main` llama `setFecha(100, 05, 1990)` e imprime `0/5/1990`: el 100 se rechaza y el día queda en el `0` de `int dia{}`.
* **[ej08](ej08_fecha_en_archivos/)** — La misma clase repartida: declaración en `fecha.h`, métodos en `fecha.cpp` con `cFecha::`. `setFecha` es el setter; `imprimir()` **no es un getter** (no devuelve nada). No hay getter.

## Constructores

Mismo nombre que la clase, sin tipo de retorno. Correr los tres y comparar la primera línea que imprimen.

* **[ej09](ej09_constructor/)** — **Predeterminado** `cFecha()`: carga `1/1/1970`. `c1.imprimir()` **antes** de cualquier `setFecha` ya imprime eso: el constructor corrió en `cFecha c1;`.
* **[ej10](ej10_constructor_parametros/)** — **Por parámetros** `cFecha(int, int, int)`, conviviendo con el anterior: la primera función **sobrecargada** (`<<` en el `ej02` era un operador). `cFecha c1 {17, 06, 1986}` usa uno; `cFecha c2;` usa el otro.
* **[ej11](ej11_valores_por_defecto/)** — **Valores por defecto** `cFecha(int day, int month = 1, int year = 1999)`: `cFecha c1 {17}` da `17/1/1999`. Los `= …` van **solo en la declaración** (el `.h`), nunca en la definición.

## El botón como clase

`v0` es el ejercicio 4 de la clase 14 tal cual (pin 21, pull-up). En `v1` **todo lo que era del botón** entra en `class Boton`; en `v2` se agrega un segundo botón.

```cpp
class Boton
{
private:
    enum STATES { buttonUp, buttonPressing, buttonDown, buttonReleasing };
    uint8_t  pin;              /* identidad */
    uint32_t antireboteMS;     /* cuanto aguanta el rebote ESTE boton */
    STATES   nextState;        /* estado actual de la maquina */
    uint32_t timeAntes;        /* reloj del antirrebote */
public:
    enum EVENTOS { SIN_EVENTO, BOTON_PRESIONADO, BOTON_SOLTADO };
    Boton( uint8_t p , uint32_t antirebote = 40 );
    EVENTOS leer( void );
};
```

* **[v0](ej12_boton_v0/)** — Sin clase. `buttonPin`, `antireboteMS`, `NextState`, `timeAntes`, los dos `enum` y `leerBoton()` sueltos en el ámbito global. Para un segundo botón hay que duplicar todo, máquina de estados incluida.
* **[v1](ej12_boton_v1/)** — `class Boton`. **Privado**: la lista de estados, el pin, el tiempo de rebote, el estado actual y el reloj (`b1.nextState = …` no compila). **Público**: `EVENTOS` (lo que el botón informa; afuera se escribe `Boton::BOTON_PRESIONADO`), el constructor y `leer()`. El constructor deja los cinco atributos con valor y hace el `pinMode`; el antirrebote tiene valor por defecto (`Boton b( 21 )` o `Boton b( 21 , 60 )`), como en el `ej11`. `Boton b;` no compila: un botón sin pin no tiene sentido. El cuerpo de `leer()` es `leerBoton()` sin una línea de lógica cambiada.
  Probar: se comporta **igual** que `v0`.
* **[v2](ej12_boton_v2/)** — `Boton b2( 20 );` y el segundo LED. Del botón, **una línea**; sin clase, eran 66. Cada objeto tiene su máquina adentro: `b1` no puede tocar el estado de `b2`.
  Probar: los dos botones, también apretados juntos.

## Errores frecuentes

* `gcc` con un `.cpp` → compila y no linkea. En C++, `g++`.
* Un número con `0` adelante es **octal**: `05` vale 5, pero `08` y `09` no compilan (`invalid digit "8" in octal constant`). Escribir `8`, no `08`.
* `class` sin `public:` → nada de afuera puede usarla, ni sus métodos.
* Repetir el valor por defecto en `cFecha::cFecha(...)` → `redefinition of default argument`.
* `std::hex` u `std::oct` y después imprimir "un número normal" → sigue saliendo en esa base.
* Tocar un `.h` y correr `make` → no recompila lo que lo incluye. `make clean && make`.
* `Boton::EVENTOS` sin el `Boton::` desde el `loop()` → `'EVENTOS' was not declared in this scope`.
