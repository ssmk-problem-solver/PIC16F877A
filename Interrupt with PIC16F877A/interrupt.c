/*
 * File:   interrupt.c
 * Author: HP
 *
 * Created on 10 July, 2024, 8:51 PM
 */


#include <xc.h>

// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>



#define _XTAL_FREQ 20000000

void interrupt isr(){
    if(INTCONbits.INTF == 1){
        PORTCbits.RC0= ~PORTCbits.RC0;
        INTCONbits.INTF=0;
    }
}

void main(void) {
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.INTE=1;
    OPTION_REGbits.INTEDG=1;
    TRISC0=0;
    while(1){
        
    }
    return;
}
