
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config CP = OFF
#pragma config BOREN = ON
#pragma config CPD = OFF
#pragma config LVP = OFF
#pragma config WRT = OFF
#pragma config DEBUG = OFF

#include <xc.h>
#define _XTAL_FREQ 20000000

#define LED1 RD0    

void main() {
    
    TRISDbits.TRISD0 = 0;
    while(1){
        
        // Single LED blink
        LED1 = 1;
        __delay_ms(1000);
        LED1 = 0;
        __delay_ms(1000); 
    }
    
}
