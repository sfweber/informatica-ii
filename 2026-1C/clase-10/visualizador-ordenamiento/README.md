# Visualizador de métodos de ordenamiento

Herramienta web para ver, **paso a paso**, cómo ordenan los 6 métodos de la unidad, con el **código en
C al lado** (se ilumina la línea que se está ejecutando). Informática II — UTN.

**Demo en vivo:** https://sfweber.github.io/informatica-ii/2026-1C/clase-10/visualizador-ordenamiento/

## Cómo se usa

Abrir `index.html` (doble clic) o entrar al demo. **No necesita internet ni instalar nada** (un solo
archivo, todo offline).

**Solapa "Paso a paso"**
- Elegí el algoritmo: Intercambio · Selección · Inserción · Burbuja · Shell · Quicksort.
- **Paso ▶ / ◀ Atrás / ⏮**, **▶ Auto** con velocidad; también flechas ←/→ y barra espaciadora.
- **Mezclar** + ejemplos (aleatorio / casi ordenado / al revés / ya ordenado) + **tus valores**.
- Flechas con los índices (`i`, `j`, `iMenor`, pivote) bajo cada elemento; `aux` flota sobre el hueco.
- **Invariante** por método, **panel de complejidad** (esperado vs real + mejor/peor caso), y
  **narración** por paso.
- **Modo predicción** (toggle): antes de cada comparación pregunta el resultado y lleva aciertos.
- En **Burbuja**, toggle **corte temprano** (variante sin `break`, bandera en el `while`): sobre
  "ya ordenado" termina en una pasada → mejor caso O(n).

**Solapa "Crecimiento: operaciones vs n"**
- Grafica operaciones (comparaciones + movimientos) para varios n, con curvas de referencia
  n / n·log n / n² y **selector de entrada**. Con "ya ordenado" se ve que Burbuja c/corte e Inserción
  caen a ~n; a n grande Shell queda muy por debajo de los básicos O(n²).

## Coherencia con la cátedra

Cada algoritmo está portado 1:1 de los `.c` de la clase-10 (Inserción y Shell ordenan por
**desplazamiento**, no por intercambios; Burbuja base **sin** corte temprano). El código que se muestra
no usa `break` (la salida temprana se expresa con condición + bandera).

## Herramientas paralelas (en C, no en el web)

Miden el **otro eje** (tiempo real, no operaciones) y van aparte:
- `visualizador-ordenamiento.c` — carrera animada en terminal.
- `codigo fuente_2024/comp_rendimientos.c` — tiempo real (`clock()`) a gran escala (quicksort vs `qsort`).

Reparto: **web = operaciones** (independiente de la máquina) · **terminal = tiempo real**.
