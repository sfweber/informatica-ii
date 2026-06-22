#include <stdio.h>

struct movie {
    int id;
    char nombre[200];
    char genero[100];
};

int main () {
    FILE *fp;
    struct movie sMovie;

    fp = fopen ("movies1.csv", "r");

    if (fp==NULL)
    {
        printf ("Error al abrir el archivo");
        return 1;
    }


    while ((fscanf (fp, " %d, %200[^,], %100s", &sMovie.id, sMovie.nombre, sMovie.genero ))== 3)
    {
        printf ("ID: %d - Nombre: %s - Genero: %s\n",
               sMovie.id, sMovie.nombre, sMovie.genero);
    }

    fclose(fp);
    getchar();
    return 0;


}
