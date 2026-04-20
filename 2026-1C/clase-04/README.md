# Clase 04

**Tema:** Manejo de archivos de texto en C — apertura, escritura secuencial, lectura secuencial, parseo de líneas, `EOF` y detección de errores de lectura.

## Ejemplos

**Tema:** Apertura y cierre

* **ejemplo01.c** — Abre `datos.txt` en modo lectura (`"r"`) y valida con `perror` si `fopen` devuelve `NULL`.
  Probar: ejecutar sin crear el archivo (ver el mensaje `No such file or directory`), luego crearlo vacío y ejecutar de nuevo.

* **ejemplo02.c** — Abre `datos.txt` en modo escritura (`"w"`) y lo cierra con `fclose`.
  Probar: ejecutar una vez y notar que se crea el archivo; ejecutar con el archivo ya existente y ver que se trunca (queda vacío).

**Tema:** Escritura secuencial

* **ejemplo03.c** — Escribe un registro formateado en `datos.txt` con `fprintf`.
  Probar: ejecutar y abrir el archivo con un editor de texto; agregar y quitar `\n` al final del formato para ver la diferencia.

* **ejemplo04.c** — Log de temperaturas en modo append (`"a"`) con `fprintf` + `fflush`, validando la entrada de `scanf`.
  Probar: ejecutarlo varias veces seguidas ingresando distintas temperaturas y verificar que el log acumula líneas (no se trunca). Luego probar con entrada inválida (letras) y ver el manejo de error.

* **ejemplo05.c** — Escribe carácter a carácter con `fputc` un nombre leído por teclado.
  Probar: ingresar un nombre de menos de 9 caracteres, luego uno de exactamente 9, luego intentar uno más largo. Notar el `%9s` en el `scanf` que evita desbordamiento.

* **ejemplo06.c** — Escribe una línea completa con `fputs` en modo append, chequeando el retorno contra `EOF` para detectar error.
  Probar: ejecutarlo varias veces seguidas y observar que `mensaje.txt` va acumulando la misma línea.

**Tema:** Lectura secuencial

* **ejemplo07.c** — Lee una fecha (`día/mes/año`) de `fechas.txt` usando `fscanf` con el formato `%d/%d/%d`.
  Probar: crear `fechas.txt` con `17/06/1986`, luego probar con formato inválido (`17-06-1986` o `hola`) y ver que el `fscanf` devuelve distinto de 3.

* **ejemplo08.c** — Lee una línea completa de `numeros.txt` con `fgets` en un buffer de 50 caracteres.
  Probar: crear un archivo con varias líneas y ver que sólo lee la primera. Probar con una línea más larga de 50 caracteres y notar el truncamiento.

**Tema:** Parseo de líneas de texto

* **ejemplo09.c** — Separa un string hardcoded `"23,45,67"` con `strtok` y convierte cada token a `int` con `atoi`. No lee archivo — muestra el mecanismo puro.
  Probar: cambiar el separador a `;` y ajustar el string. Cambiar a `atof` con `"1.5,2.7,3.14"`. Imprimir `linea` después del `while` para ver que el string original queda roto (reemplazado por `\0` en cada separador).

* **ejemplo10.c** — Caso real: lee `datos.csv` (sensor, temperatura, humedad) con `fgets` y parsea cada línea con `strtok` + `atof`.
  Probar: ejecutar tal cual. Luego editar `datos.csv` agregando más sensores. Probar qué pasa si una línea tiene una coma de menos (spoiler: `atof(NULL)` revienta).

**Tema:** EOF, `feof` y errores de lectura

* **ejemplo11.c** — Copia desde teclado (`stdin`) a archivo (`teclado.txt`) con `getchar`/`fputc`. El loop termina cuando el usuario envía `EOF`.
  Probar: escribir varias líneas y cerrar con `Ctrl+D` (Linux) o `Ctrl+Z` + Enter (Windows). Abrir `teclado.txt` y verificar el contenido.

* **ejemplo12.c** — Lee un archivo grande desde un pendrive (`/mnt/pendrive/archivo_grande.txt`) carácter por carácter con `usleep(100)` entre cada uno. Al terminar, imprime *"Archivo leido completamente... (?)"*.
  Probar: generar el archivo con `creador_archivo_10MB.c` en un pendrive, ajustar la ruta al punto de montaje correcto, y desconectar el pendrive mientras se está leyendo. Observar que el programa reporta lectura exitosa aunque sólo leyó una fracción — el `EOF` fue por error, no por fin de archivo.

* **ejemplo13.c** — Igual que el 12 pero agrega `feof(fp)` después del loop para distinguir fin de archivo real vs interrupción.
  Probar: repetir el experimento del pendrive del ejemplo12 y ver ahora que el programa imprime *"La lectura terminó pero no por fin de archivo"*. Dejar que termine sin desconectar y ver el mensaje de fin exitoso.

**Utilidad auxiliar**

* **creador_archivo_10MB.c** — Genera `archivo_grande.txt` de 10 MB con caracteres ASCII imprimibles aleatorios. Usar para preparar el experimento de los ejemplos 12 y 13.
  Probar: compilarlo y ejecutarlo. Por defecto crea el archivo en el directorio actual. Copiar el archivo resultante al pendrive antes de correr `ejemplo12.c` / `ejemplo13.c`.
