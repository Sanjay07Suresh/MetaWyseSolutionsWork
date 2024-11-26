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
#define en RC1
#define sw RD1

void lcd_init();
void uart_init();
void timer1_init();
unsigned int countvalue();
void tx(unsigned char);
void txstr(unsigned char*);
void cmd(unsigned char);
void dat(unsigned char);
void show(unsigned char*);

void main() {
    TRISDbits.TRISD1 = 1;
    OPTION_REGbits.nRBPU = 0;
    lcd_init();
    uart_init();
    timer1_init();

    while(1) {
        unsigned int c = countvalue();
        char buffer[10];
        
        cmd(0x01);
        sprintf(buffer, "Count: %u", c);
        show(buffer);

        sprintf(buffer, "%u", c);
        txstr(buffer);
        tx('\r');
        tx('\n');

        __delay_ms(1000);
    }
}

void uart_init() {
    TRISC |= (1 << 7);
    TRISC &= ~(1 << 6);
    TXSTA = 0x20;
    RCSTA = 0x90;
    SPBRG = 31;
}

void lcd_init() {
    TRISB = 0x00;
    TRISCbits.TRISC0 = 0; 
    TRISCbits.TRISC1 = 0; 
    cmd(0x38);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x01);
    __delay_ms(2);
}

void timer1_init() {
    T1CON = 0x31;
}

void cmd(unsigned char a) {
    PORTB = a;
    rs = 0;
    en = 1;
    __delay_ms(2);
    en = 0;
}

void dat(unsigned char b) {
    PORTB = b;
    rs = 1;
    en = 1;
    __delay_ms(2);
    en = 0;
}

void show(unsigned char *s) {
    while (*s) {
        dat(*s++);
    }
}

void tx(unsigned char a) {
    while (!TXIF);
    TXREG = a;
}

void txstr(unsigned char *b) {
    while (*b) {
        tx(*b++);
    }
}

unsigned int countvalue() {
    unsigned int c = 0;

    for(unsigned int i = 0;i<(9*60);i++){
        TMR1H = 0;
        TMR1L = 0;
        TMR1IF = 0;
        while(!TMR1IF){
            if(!sw){
            __delay_ms(20); //pushbutton debounce
            c++;
            while(!sw); //this will keep the control in loop till button is released
            }
        }
        TMR1IF = 0;
    }
    return c;
}

