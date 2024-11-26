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

void ser_int();
void tx(unsigned char);
unsigned char rx();
void txstr(unsigned char*);

void main() {
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;
    ser_int();
    txstr("Enter the string:\n\r\r");
    while(1){
        tx(rx());
    }
    
}

void ser_int(){
    TXSTA = 0x20;
    RCSTA = 0x90;
    SPBRG = 31;

}

void tx(unsigned char a){
    
    while(!TXIF);
    TXREG = a;
}

unsigned char rx(){
    while(!RCIF);
    return RCREG;
}

void txstr(unsigned char *a){
    while(*a){
        tx(*a++);
    }
}