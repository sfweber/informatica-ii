#include <stdio.h>

int suma (int a, int b)
{
    return a + b ;
}


int main(void)
{
    int (*ejemploPtr)() = &suma;

    int x, y, z;
    x=30;
    y=2*x;

    //z = ejemploPtr (x,y);
    z = (*ejemploPtr)(x,y);

    printf ("La suma es: %d", z);

    getchar();
    return 0;
}
