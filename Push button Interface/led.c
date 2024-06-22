/*
 * File:   led.c
 * Author: HP
 *
 * Created on 9 March, 2024, 10:50 PM
 */
#define _XTAL_FREQ 20000000

// 'C' source line config statements
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>

void main(void) {
    TRISB7=0;
    TRISB0=1;
    while(1)
    {  
       int a;
       a=PORTBbits.RB0;
        if(a==1){

        PORTBbits.RB7=1;
        __delay_ms(1000);}
        PORTBbits.RB7=0;// PIC16F877A Configuration Bit Settings
       __delay_ms(1000);
    };
    return;
}
