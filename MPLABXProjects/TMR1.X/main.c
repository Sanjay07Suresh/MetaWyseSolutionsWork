
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config CP = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config DEBUG = OFF


#include <xc.h>

#define _XTAL_FREQ 20000000
#define LED RD0

void t1Delay();

void main() {
    TRISDbits.TRISD0 = 0 ;
    T1CON = 0x31;
    while(1){
        LED = 1;
        t1Delay();
        LED = 0;
        t1Delay();
    }
    
}
void t1Delay(){
    for(int i=0; i<9; i++){
        TMR1H = TMR1L = 0;
        while(!TMR1IF);
        TMR1IF=0;
    }
} 