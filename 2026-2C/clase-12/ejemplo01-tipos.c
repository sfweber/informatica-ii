#include <stdio.h>
#include <limits.h>

int main () {



        printf ("El tamanio en bytes de char es %zu\n", sizeof(char));
        printf ("El rango de char es %d - %d\n\n", CHAR_MIN, CHAR_MAX);

        printf ("El tamanio en bytes de unsigned char es %zu\n", sizeof(unsigned char));
        printf ("El rango de unsigned char es 0 - %u\n\n", UCHAR_MAX);

        printf ("El tamanio en bytes de short es %zu\n", sizeof(short));
        printf ("El rango de short es %d - %d\n\n", SHRT_MIN, SHRT_MAX);

        printf ("El tamanio en bytes de unsigned short es %zu\n", sizeof(unsigned short));
        printf ("El rango de unsigned short es 0 - %d\n\n", USHRT_MAX);

        printf ("El tamanio en bytes de int es %zu\n", sizeof(int));
        printf ("El rango de  int es %d - %d\n\n", INT_MIN, INT_MAX);

        printf ("El tamanio en bytes de un unsigned int es %zu\n", sizeof (unsigned int));
        printf ("El rango de  unsigned int es 0 - %u\n\n", UINT_MAX);

        printf ("El tamanio en bytes de long es %zu\n", sizeof (long));
        printf ("El rango de  long es %ld - %ld\n\n", LONG_MIN, LONG_MAX);

        printf ("El tamanio en bytes de unsigned long es %zu\n", sizeof (unsigned long));
        printf ("El rango de unsigned long es 0 - %lu\n\n", ULONG_MAX);

        printf ("El tamanio en bytes de long long es %zu\n", sizeof (long long));
        printf ("El rango de  long long es %lld - %lld\n\n", LLONG_MIN, LLONG_MAX);

        printf ("El tamanio en bytes de unsigned long long es %zu\n", sizeof (unsigned long long));
        printf ("El rango de unsigned long long es 0 - %llu\n\n", ULLONG_MAX);
}
