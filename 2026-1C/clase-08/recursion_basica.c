
#include<stdio.h>

int fr(int);

int main(void)
{
    int i;
    i=fr(3);
    printf("\ni=%d \n",i);
    return 0;
}

int fr(int i)
{
    if (i!=6) {
        printf("\ni=%d",i);
        i=fr(i+1);
    }
    return i;
}

