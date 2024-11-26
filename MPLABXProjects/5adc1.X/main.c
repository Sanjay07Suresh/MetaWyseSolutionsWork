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

void lcd_init(void);
void adc_init(void);
void cmd(unsigned char);
void dat(unsigned char);
void show(unsigned char*);
void adc(unsigned char);



void main(void) {
    lcd_init();
    adc_init();
    show((unsigned char*)"ADC VALUE: ");
    while(1){
        cmd(0x8B);
        adc(0b000);
        cmd(0xC0);
        adc(0b001);
        cmd(0xC5);
        adc(0b010);
        cmd(0xCA);
        adc(0b011);
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

void lcd_init(){
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC2 = 0;
    TRISB = 0;
    cmd(0x38);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x80);
    __delay_ms(2);
}

void adc_init(){
    TRISA = 0x0f;
    ADCON0 = 0x81;
    ADCON1 = 0xC0;
}

void adc(unsigned char ch){
    unsigned int adcvalue;
    ADCON0 &= (0xC3);
    ADCON0 |= (ch<<3);
    
    GO_nDONE = 1;
    
    while(GO_nDONE);
    
    adcvalue = ((ADRESH << 8)|(ADRESL));
    
    dat((adcvalue/1000)+48);
    dat(((adcvalue/100)%10)+48);
    dat(((adcvalue/10)%10)+48);
    dat(((adcvalue/1)%10)+48);
    
}
    