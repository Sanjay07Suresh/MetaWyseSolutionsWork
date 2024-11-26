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

void t2Delay();

void main() {
    
    TRISDbits.TRISD0 = 0;
    T2CON = 0x78;
    while(1){
        LED = 1;
        t2Delay();
        LED = 0;
        t2Delay();
    }
    
}
void t2Delay(){
    unsigned int i;
    T2CON |= (1<<2);
    for(i=0;i<1220;i++){
        while(!TMR2IF);
        TMR2IF = 0;
    }
} 