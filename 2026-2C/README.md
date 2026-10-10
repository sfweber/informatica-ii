# Segundo Cuatrimestre 2026

Material clase a clase. Cada carpeta contiene los scripts vistos en clase.
La numeración continúa la del primer cuatrimestre (que terminó en la clase 11).

<!-- REGLA: toda clase-NN/ que entra al repo lleva su fila en esta tabla EN EL MISMO COMMIT.
     Check (desde esta carpeta): for d in clase-*/; do grep -q "${d%/}" README.md || echo "FALTA $d"; done -->
| Clase | Tema |
|-------|------|
| [clase-12](clase-12/) | Representación de números reales: punto fijo (BSS/SM, rango, resolución, truncar vs redondear) y punto flotante IEEE 754 (mantisa, exponente, denormales, precisión de `float`/`double`) |
| clase-13 | Introducción a microcontroladores (Arduino Mega 2560, capas ISA → core → placa, toolchain `arduino-cli`, hola mundo) — sin código en el repo; el material está en el campus |
| [clase-14](clase-14/) | Entradas digitales y máquinas de estado en el micro: nivel vs flanco, rebote, antirrebote como MEF, `delay()` vs `millis()`, dos temporizadores conviviendo, driver `leerBoton()` vs aplicación (Wokwi, Mega 2560) |
| [clase-15](clase-15/) | Interrupciones de hardware: pines de interrupción externa y `digitalPinToInterrupt()`, la ISR y qué no va adentro, `volatile` y sección crítica, y cómo la interrupción se conecta con la MEF del antirrebote sin tocar la aplicación (Wokwi, Mega 2560) |
| [clase-16](clase-16/) | Introducción a C++: flujos `cout`/`cin`, varios archivos y header guards, `std::`, clases (`private`/`public`, encapsulamiento) y constructores (predeterminado, por parámetros, valores por defecto); cierre con el botón de la clase 14 como `class Boton` (Wokwi) |
| [clase-17](clase-17/) | Memoria dinámica en C++ y destructores: `new`/`delete` y `new[]`/`delete[]`, puntero colgante y fugas con `new`, el destructor; `miVector` y `miString` (memoria pedida en el constructor y liberada en el destructor, objetos creados con `new`) |
| [clase-18](clase-18/) | Listas simplemente enlazadas, parte 1: `Nodo` y `Lista`, `crearLista`, recorrer, destructor, insertar al principio y al final |
