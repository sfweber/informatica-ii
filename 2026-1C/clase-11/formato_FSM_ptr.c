// PLANTILLA de FSM con punteros a función (el molde break-free; no es un tipo Moore/Mealy).
// Las funciones state_0..state_n las definís vos; por eso este molde solo no linkea.

// 1. Definimos el tipo de función para los estados
typedef void (*StateFunc)(void);   // (void) = no recibe parametros; adaptalo si necesitas

// 2. Prototipos de las funciones que representan los estados
void state_0(void);
void state_1(void);
void state_2(void);
// ...
void state_n(void);

// 3. Variable que apunta al estado actual
StateFunc nextState;

int main(void) {
    // 4. Estado inicial
    nextState = state_0;

    while (1) {              /* reemplaza por tu condicion de salida */
        nextState();        // ejecutar el estado actual
    }
    return 0;
}
