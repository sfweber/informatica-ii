# Ayuda TP1 — Parseo de `movies.csv`

Material de apoyo para el **TP1 "Archivos cruzados"**. El punto 2 del TP requiere
concatenar `movies2.csv` (texto) a `movies1.dat` (binario); el paso previo es leer
correctamente el archivo de texto. Los ejemplos abordan el problema de forma
progresiva: desde `fscanf` sobre un archivo simple hasta el manejo de títulos con
comas y comillas como los del conjunto de datos MovieLens.

Cada ejemplo está en su subcarpeta junto al archivo de datos que utiliza. Para
ejecutarlos hay que compilar y correr **dentro de la subcarpeta correspondiente**,
ya que cada programa abre su archivo por ruta relativa.

## Compilación y ejecución

```bash
cd 01-fscanf-basico
gcc -Wall -Wextra -std=c11 ejemplo01.c -o ejemplo01
./ejemplo01
```

En Windows con MinGW el ejecutable se genera con extensión `.exe`.

## Ejemplos

### `01-fscanf-basico/` — `ejemplo01.c`

Parseo de un archivo con campos separados por espacios (`%d %f %s`). Introduce
`fscanf` y el control del bucle mediante su valor de retorno (la cantidad de campos
leídos correctamente). Ejecutar y verificar que lee las dos líneas de `datos.txt`.

### `02-separador-coma/` — `ejemplo02.c`

Igual que el anterior pero con campos separados por comas; las comas se incluyen en
la cadena de formato (`%d, %f, %s`).

### `03-scanset/` — `ejemplo03_A.c`, `ejemplo03_B.c`, `ejemplo03_C.c`

Lectura de campos de texto que pueden contener espacios o el propio separador.
Conviene ejecutarlos en orden, ya que cada uno corrige una limitación del anterior.

- **`ejemplo03_A.c`** — Intento con `%s` para el campo de texto. No funciona: `%s`
  lee hasta el primer espacio en blanco, y como la línea no contiene espacios captura
  todo el contenido (incluidas las comas y los números), por lo que no quedan datos
  para los campos `%d` y `%f`. `fscanf` devuelve 1 en lugar de 3 y el bucle no llega a
  ejecutarse: el programa **no imprime nada**, y esa ausencia de salida es el resultado
  esperado que demuestra que `%s` no sirve para este caso.
- **`ejemplo03_B.c`** — Uso del scanset `%[^,]` (leer hasta encontrar una coma), que
  permite capturar texto con espacios. A partir de la segunda línea, el salto de
  línea queda incluido al comienzo del texto (la salida muestra `Texto:` y el nombre
  en el renglón siguiente). Esa es la limitación que resuelve el ejemplo siguiente.
- **`ejemplo03_C.c`** — Se antepone un espacio en la cadena de formato para que
  `fscanf` ignore espacios en blanco y saltos de línea previos al valor. La salida
  queda correcta en todas las líneas.

### `04-comillas/` — `ejemplo04.c`

Lectura de texto delimitado por comillas dobles mediante el scanset `%[^"]`.

### `05-caso-real/` — `ejemplo05_A.c`, `ejemplo05_B.c`, `ejemplo05_C.c`

Aplicación sobre `movies1.csv`.

- **`ejemplo05_A.c`** — Parser directo. Procesa correctamente los primeros registros
  hasta llegar a un título entrecomillado que contiene una coma (id 11,
  `"American President, The (1995)"`), donde se desincroniza y se detiene. Evidencia
  que el formato del CSV no es trivial.
- **`ejemplo05_B.c`** — Solución: si el título comienza con comilla doble, se lee
  hasta la comilla de cierre; en caso contrario se retrocede un carácter con
  `fseek(fp, -1, SEEK_CUR)` y se lee hasta la coma. Procesa todos los registros,
  incluido el id 11.
- **`ejemplo05_C.c`** — Ejemplo de `strtok` para dividir una cadena en tokens según
  un separador.

## Datos

El archivo `05-caso-real/movies1.csv` es una **muestra reducida (20 películas)**,
suficiente para ejecutar los ejemplos sin descargas adicionales. El `movies1.csv`
completo se encuentra en el campus virtual.

## Alcance

Estos ejemplos cubren la lectura del archivo de texto. El resto corresponde al
desarrollo del TP:

- En el CSV el género figura como texto (`Comedy|Drama|Romance`), mientras que el
  struct del TP (`include/tp1.h`) lo representa como un conjunto de 19 flags. La
  conversión entre ambas representaciones forma parte del trabajo a resolver.
- Los géneros con guion aparecen en el CSV como `Sci-Fi` y `Film-Noir`, en tanto que
  los campos del struct se denominan `SciFi` y `FilmNoir`. Además, existen películas
  con el valor `(no genres listed)`.
