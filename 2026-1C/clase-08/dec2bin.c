#include <stdio.h>

void dec2bin(int );

int main() {

    int n = 251;

    printf ("decimal = %d \nbinario = ", n);
    dec2bin (n);
    printf ("\n");
    return 0;
}
void dec2bin (int n) {
    if (n == 0)
        return;
    dec2bin (n/2);
    printf ("%d", n%2);

}