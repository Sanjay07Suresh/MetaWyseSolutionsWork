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

void t_init();
void uart_init();
void t2delay();
void t1delay();
void tx(unsigned char);
void txstr(unsigned char*);
unsigned int adc();
void adc_init();

void main(){
    adc_init();
    t_init();
    uart_init();
    while(1){
        char buffer[10];
         
        t1delay();
        unsigned int adcvalue = adc();
        sprintf(buffer,"%d",adcvalue);
        
        txstr(buffer);
        tx('\r');
        tx('\n');
        t2delay();

    }
}
void adc_init(){
    TRISA |= (1<<0); 
    ADCON0 = 0x41; 
    ADCON1 = 0x80; 
}
void t_init(){
    T1CON = 0x31;
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
void t1delay(){
    for(int i = 0;i<(9*5);i++){
        TMR1H=TMR1L=0;
        while(!TMR1IF);
        TMR1IF=0;
    }
    
}
void t2delay(){
    T2CON |= (1<<2);
    for(unsigned int i = 0; i<(1220*5); i++){
        while(!TMR2IF);
        TMR2IF = 0;
    }
}
unsigned int adc(){
    unsigned int adcvalue;
    __delay_ms(2); 
    ADCON0bits.GO_nDONE = 1; 
    
    while(ADCON0bits.GO_nDONE);
    adcvalue = (ADRESH << 8) | ADRESL; 
    return adcvalue;
}