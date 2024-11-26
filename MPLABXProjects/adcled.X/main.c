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
#define _XTAL_FREQ 20000000

void led_init(void);
void adc_init(void);
unsigned int adc(unsigned char);

void main(void) {
    led_init();
    adc_init();
    
    while(1){
        unsigned int adca[4];
        for(unsigned char i = 0;i<4;i++){
            adca[i]=adc(i);
            __delay_ms(5);
        }
        for(unsigned char i=0;i<4;i++){
            if(adca[i]>=500){
                PORTB |= (1<<i);
                __delay_ms(1000);
                PORTB &= ~(1<<i);
                __delay_ms(1000);
            }else if(500>adca[i] && adca[i]>=300){
                PORTB |= (1<<i);
            }else{
                PORTB &= ~(1<<i);
            }
        }
    }
   
}

void adc_init(){
    TRISA = 0x0F; 
    ADCON0 = 0x41; 
    ADCON1 = 0x80; 
}

void led_init(){
    TRISB = 0x00; 
    PORTB = 0x00; 
}

unsigned int adc(unsigned char ch){
    unsigned int adcvalue;
    ADCON0 &= 0xC7; 
    ADCON0 |= (ch << 3); 
    __delay_ms(2); 
    ADCON0bits.GO_nDONE = 1; 
    
    while(ADCON0bits.GO_nDONE);
    adcvalue = (ADRESH << 8) | ADRESL; 
    return adcvalue;
}
