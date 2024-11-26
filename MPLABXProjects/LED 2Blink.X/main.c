
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
#define LED2 RD1

void main() {
    
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    
    while(1){
       
         // Two LED blink alternate
         LED1 =  1;
         LED2 = 0;
         __delay_ms(1000);
         
         LED1 =  0;
         LED2 = 1;
         __delay_ms(1000);
         
    }
}