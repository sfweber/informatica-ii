/* Ejemplo 2 (versión con PUNTEROS A FUNCIÓN) — detector "abcd", correcto.
 * Maneja bien el reinicio ante 'a' (a diferencia de la versión con switch). TIPO: Mealy. */
#include <stdio.h>


// 1. Definimos el tipo de función para los estados
typedef void (*StateFunc)(char);  // Puede adaptarse si necesitás parámetros

// 2. Prototipos de las funciones que representan los estados
void state_A (char);
void state_B (char);
void state_C (char);
void state_D (char);

// 3. Variable que apunta al estado actual
StateFunc nextState;

int main(void) {
    int c;
    // 4. Estado inicial
    nextState = state_A;

    c = getchar ();
    while (c != EOF) {
        if (c != '\n')          // ignora el Enter (no es parte del alfabeto)
            nextState ( c );    // Ejecutar estado actual
        c = getchar ();
    }
    return 0;
}

void state_A(char c)
{
    if ( c != 'a')
    {
        printf ("Secuencia incorrecta.\n");
        nextState = state_A ;
    }
    else
        nextState = state_B ;

}
void state_B(char c)
{
    if ( c != 'b' && c != 'a')
    {
        printf ("Secuencia incorrecta.\n");
        nextState = state_A ;
    }
    else if ( c == 'a')
        nextState = state_B ;
    else
        nextState = state_C ;

}
void state_C(char c)
{
    if ( c != 'c' && c != 'a')
    {
        printf ("Secuencia incorrecta.\n");
        nextState = state_A ;
    }
    else if ( c == 'a' )
        nextState = state_B;
    else
        nextState = state_D ;
}
void state_D(char c)
{
    if ( c == 'd')
    {
        printf ("Secuencia correcta. Lanzando misiles.\n");
        nextState = state_A;
    }
    else if ( c == 'a')
        nextState = state_B ;
    else
    {
        printf ("Secuencia incorrecta.\n");
        nextState = state_A;
    }
}
