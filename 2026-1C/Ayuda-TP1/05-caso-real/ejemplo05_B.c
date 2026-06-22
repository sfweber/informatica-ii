#include <stdio.h>

struct movie {
    int id;
    char nombre[200];
    char genero[100];
};

int main() {
    FILE *fp;
    struct movie sMovie;

    fp = fopen("movies1.csv", "r");

    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    // Ajustamos el formato para manejar las comillas y las comas dentro del nombre
    while (fscanf(fp, " %d,", &sMovie.id) == 1) {
        // Leer el nombre de la película, considerando las comillas
        if (fgetc(fp) == '"') {
            // Si comienza con comillas, lee hasta las comillas dobles de cierre
            fscanf(fp, " %199[^\"]\"", sMovie.nombre);
        } else {
            // Si no hay comillas, retrocede un carácter y lee normalmente hasta la coma
            fseek(fp, -1, SEEK_CUR);
            fscanf(fp, " %199[^,]", sMovie.nombre);
        }
        // Leer el género después de la coma
        fscanf(fp, ", %99[^\n]", sMovie.genero);

        // Imprimir la película
        printf("ID: %d, Nombre: %s, Genero: %s\n", sMovie.id, sMovie.nombre, sMovie.genero);
    }

    fclose(fp);
    return 0;
}
