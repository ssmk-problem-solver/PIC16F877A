/*
 * File:   PWM_LED_fading.c
 * Author: HP
 *
 * Created on 4 August, 2024, 1:51 PM
 */


#include <xc.h>

#define _XTAL_FREQ 20000000

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







void setpwm(unsigned int dutycycle){
    
    
    CCPR1L = dutycycle >> 2; // 8 MSB BITS TO THE CCPR1L REGISTER
    
   // dutycycle= 0x30 & (dutycycle<<4);   // TO SHIFT LSBS  2BITS TO 4TH AND 5TH PLACE AND MAKE MASKING IT
    
    CCP1CON =CCP1CON & 0xCF;  // TO MAKE 4TH 5TH BITS TO ZERO
    
    CCP1CON = CCP1CON | (0x30 & (dutycycle<<4)); 

}




 unsigned int i=0;



void main(void) {
    
    TRISC=0;   //TO MAKE CCP1 AS OUTPUT
    
    CCP1CON = 0x0C;  // PWM MODE IN CCP1CON
    
    PR2=0xFF; // FREQUECY SET FOR TIMER
    
    T2CON = 0x04;  // timer 2 is on
    
    
    
    

    for(i=0;i<1023;i++){
        setpwm(i);
        __delay_ms(2);
    }
    for(i=1023;i>0;i--){
        setpwm(i);
        __delay_ms(2);
    }
    
    return;
}
