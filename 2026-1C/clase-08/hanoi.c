#include <stdio.h>

// Torres de hanoi
void hanoi(int, char, char, char );

int main() {

    int n = 4;

    hanoi (n, 'A', 'B', 'C');
    return 0;
}
void hanoi (int n, char origen, char auxiliar, char destino) {
    if (n == 1)
    {
        printf ("Mover de %c a %c\n", origen, destino);
        return;
    }
    hanoi ((n-1), origen, destino, auxiliar);
    printf ("Mover de %c a %c\n", origen, destino);
    hanoi ((n-1), auxiliar, origen, destino);

}

