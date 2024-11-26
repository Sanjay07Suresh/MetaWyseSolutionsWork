
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

void t0Delay();

void main() {
    TRISDbits.TRISD0 = 0;
    OPTION_REG = 0x07;
    while(1){
        LED = 1;
        t0Delay();
        LED = 0;
        t0Delay();
    }
    
}
void t0Delay(){
    for(int i=0; i<76; i++){
        while(!T0IF);
        T0IF=0;
    }
} 