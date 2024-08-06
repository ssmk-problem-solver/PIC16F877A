/*
 * File:   Uart.c
 * Author: HP
 *
 * Created on 6 August, 2024, 7:18 PM
 */

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


#include<xc.h>



unsigned char rx_dta=0;



void tx(unsigned char data){
    if(PIR1bits.TXIF==1){
        TXREG= data;
        PIR1bits.TXIF=0;
    }
}

void tx_string(const char *str,unsigned char num){
    
    for(int i=0;i<num;i++){
        tx(str[i]);
    }
}


void interrupt ISR(){
    
    
    if (PIR1bits.RCIF==1){
    rx_dta = (RCREG);
    PIR1bits.RCIF=0;
    }
}





void main(void) {
    
    TRISC=0x02;
    TRISB=0x00;
    
    TXSTA=0x24;
    RCSTA =0x90;
    
    //char str[];
    
    while(1){
        
      char  str[]= "mani";
        tx_string(str,4);
        
        if(rx_dta =='a'){
            PORTBbits.RB0=1;
        }
        else if (rx_dta =='b'){
            PORTBbits.RB0=0;
        }
    }
    return;
}
