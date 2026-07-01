/* PLANTILLA de FSM con switch-case + enum (es el molde, no un tipo Moore/Mealy) */
typedef enum {
    STATE_0,
    STATE_1,
    STATE_2,
    //
    //
    STATE_N
} STATES;



int main(void){

    STATES NextState;
    
    NextState = STATE_0 ;
    
    while (1) {          /* reemplaza por tu condicion de salida */
        switch (NextState) {
        case STATE_0:
            //Code to run when STATE_0
            if ( X == Y)
                NextState = STATE_1;
            else
                NextState = STATE_N;
            break;
            
        case STATE_1:
            //
            
            break;
          
        default:
            // When the selected State has not defnied show an error...
            break;
        }
        
    }
}
