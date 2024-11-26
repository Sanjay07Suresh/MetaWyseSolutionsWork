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

#define sw RB0     //switch input
#define LED RD0    //LED output


void main() {
    
    TRISBbits.TRISB0 = 1; // configure RB0 as input
    TRISDbits.TRISD0 = 0; // configure RD0 as output
    OPTION_REGbits.nRBPU = 0;
    unsigned int c = 0;
    LED = 0;
    while(1){
        if(!sw){
            __delay_ms(20); //pushbutton debounce
            c++;
            while(!sw); //this will keep the control in loop till button is released
        }
        if(c==2){
            LED = !LED;
            c=0;
        }
    }
}