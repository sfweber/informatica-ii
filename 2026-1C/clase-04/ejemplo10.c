#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char linea[100];
    char *sensor, *temp_s, *hum_s;
    float temp, hum;

    fp = fopen("datos.csv", "r");
    if (fp == NULL) {
        perror("Error abriendo archivo");
        return 1;
    }

    while (fgets(linea, sizeof(linea), fp) != NULL) {
        sensor = strtok(linea, ",");
        temp_s = strtok(NULL, ",");
        hum_s  = strtok(NULL, ",");

        temp = atof(temp_s);
        hum  = atof(hum_s);

        printf("Sensor: %s | T: %.1f°C | H: %.1f%%\n",
               sensor, temp, hum);
    }

    fclose(fp);
    return 0;
}