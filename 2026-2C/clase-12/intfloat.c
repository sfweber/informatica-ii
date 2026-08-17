#include <stdio.h>

int main(void) {
    int i;
    int vuelve;
    float f;
    

    for (i = 16777215; i <= 16777221; i++) {
        f = i;          /* int -> float */
        vuelve = f;     /* float -> int */

        if (i == vuelve) {
            printf("%d -> float -> %d\n", i, vuelve);
        } else {
            printf("%d -> float -> %d   <-- SE PERDIO\n", i, vuelve);
        }
    }
    return 0;
}
