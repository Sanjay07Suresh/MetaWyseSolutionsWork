#pragma config FOSC = HS
#pragma config PWRTE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config DEBUG = OFF

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000

void t2_init();
void uart_init();
void t2delay();
void tx(unsigned char);
void txstr(unsigned char*);

void main(){
    t2_init();
    uart_init();
    unsigned char i=0;
    while(1){
        tx(i);
        i++;
        txstr('\r\n');
        t2delay();
    }
    
}

void t2_init(){
    T2CON = 0x78;
}
void uart_init(){
    TRISC |= (1<<7);
    TRISC &= ~(1<<6);
    TXSTA = 0x20;
    RCSTA = 0x90;
    SPBRG = 31;
}
void tx(unsigned char a){
    while(!TXIF);
    TXREG = a;
}
void txstr(unsigned char *b){
    while(*b){
        tx(*b++);
    }
}
void t2delay(){
    T2CON |= (1<<2);
    for(unsigned int i = 0; i<1220; i++){
        while(!TMR2IF);
        TMR2IF = 0;
    }
}