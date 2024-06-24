/*
 * File:   lcd_interfacing.c
 * Author: HP
 *
 * Created on 6 April, 2024, 3:13 PM
 */

#include <xc.h>

#define _XTAL_FREQ 20000000
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN  PORTDbits.RD2
void dataloop(unsigned char data){
    PORTC=data;
    RS=1;
    RW=0;
    EN=1;
    __delay_ms(5);
    EN=0;
    
}

void instructionloop(unsigned char cmd){
    PORTC=cmd;
    RS=0;
    RW=0;
    EN=1;
    __delay_ms(5);
    EN=0;
    
}

void string(const unsigned char *str,unsigned char num){
    unsigned char i;
    for(i=0;i<num;i++){
        dataloop(str[i]);
    }
}

void initialization(){      // command to lcd settings
    instructionloop(0x38);  //16x2
    instructionloop(0x06);  //cursor to next element
    instructionloop(0x0C);  //lcd on cursor off
    instructionloop(0x01);  //clear
}
void main(void) {
    
    TRISC=0x00;
    TRISD=0x00;
    initialization();
    while(1){
        instructionloop(0x80);
        string("EMBEDDED SYSTEMS",0x0F);
        instructionloop(0xC0);
        string("BY SUBA",7);
    }
    return;
}
