#pragma config FOSC = HS
#pragma config PWRTE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config DEBUG = OFF


#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
#define rs RC0
#define en RC2

void lcd_init();
void cmd(unsigned char);
void dat(unsigned char);
void show(unsigned char*);
void adc(void);

void lcd_init(){
    cmd(0x38);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x80);
    __delay_ms(2);
}

void main() {
    TRISAbits.TRISA0 = 1;
    TRISB = 0x00;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC2 = 0;
    lcd_init();
    show((unsigned char*)"ADC VALUE: ");
    
    while(1){
        cmd(0x8C);
        adc();
    }
    
    
}

void cmd(unsigned char a){
    PORTB = a;
    rs = 0;
    en = 1;
    __delay_ms(2);
    en = 0;   
}


void dat(unsigned char b){
    PORTB = b;
    rs = 1;
    en = 1;
    __delay_ms(2);
    en = 0;   
}

void show(unsigned char *s){
    while(*s){
        dat(*s++);
    }
}

void adc(){
    unsigned int adcvalue;
    
    ADCON1 = 0xC0;
    ADCON0 = 0x85;
    
    while(GO_nDONE);
    adcvalue=(ADRESH << 8)|(ADRESL);
    
    dat((adcvalue/1000)+48);
    dat(((adcvalue/100)%10)+48);
    dat(((adcvalue/10)%10)+48);
    dat(((adcvalue/1)%10)+48);
}