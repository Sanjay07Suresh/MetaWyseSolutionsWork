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

void ser_init();
void adc_init();
void tx(unsigned char);
void txstr(unsigned char*);
unsigned char rx();
unsigned int adc();

void main(){
    ser_init();
    adc_init();
    while(1){
        unsigned int adcvalue = adc();
        unsigned char buffer[20];
        sprintf(buffer, "ADC VALUE: %u", adcvalue);
        txstr(buffer);  
        /*
        tx('\r');
        tx('\n');
         */
        txstr('\r\n');
        __delay_ms(1000);
        
    } 
}

void ser_init(){
    TXSTA = 0x20;
    RCSTA = 0x90;
    SPBRG = 31;
}
void adc_init(){
    TRISAbits.TRISA0 = 1;
    ADCON0 = 0x41;
    ADCON1 = 0x80;
} 
void tx(unsigned char a){
    while(!TXIF);
    TXREG = a;
}
unsigned char rx(){
    while(!RCIF);
    return RCREG;
}
void txstr(unsigned char* a){
    while(*a){
        tx(*a++);
    }
}
unsigned int adc(){
    
    unsigned int adcvalue;
    ADCON0bits.GO_nDONE = 1;
    
    while(ADCON0bits.GO_nDONE);
    adcvalue = (ADRESH<<8)|(ADRESL);
    return adcvalue;
    
}
