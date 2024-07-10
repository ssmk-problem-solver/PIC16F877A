/*
 * File:   keypad.c
 * Author: HP
 *
 * Created on 5 July, 2024, 7:14 PM
 */

#define _XTAL_FREQ 20000000


// PIC16F877A Configuration Bit Settings
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

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define E PORTCbits.RC2

#define C0 PORTBbits.RB0
#define C1 PORTBbits.RB1
#define C2 PORTBbits.RB2

#define R0 PORTBbits.RB4
#define R1 PORTBbits.RB5
#define R2 PORTBbits.RB6
#define R3 PORTBbits.RB7


#include <xc.h>

void lcd_command(unsigned char cmd){
    PORTD=cmd;
    RS=0;
    RW=0;
    E=1;
    __delay_ms(5);
    E=0;
    
}
void lcd_data(unsigned char data){
    PORTD=data;
    RS=1;
    RW=0;
    E=1;
    __delay_ms(5);
    E=0;
 }

void lcd_string(unsigned char arr[],int len){
    for(int i=0;i<len;i++){
        lcd_data(arr[i]);
        
   }
}

void lcd_initialize(){
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}


keypad(){
    C0=1,C1=0,C2=0;
    if(R0==1){
        lcd_data('1');
        while(R0==1);
    }
    if(R1==1){
        lcd_data('4');
        while(R1==1);
    }
    if(R2==1){
        lcd_data('7');
        while(R2==1);
    }
    if(R3==1){
        lcd_data('*');
        while(R3==1);
    }

    C0=0,C1=1,C2=0;
    if(R0==1){
        lcd_data('2');
        while(R0==1);
    }
    if(R1==1){
        lcd_data('5');
        while(R1==1);
    }
    if(R2==1){
        lcd_data('8');
        while(R2==1);
    }
    if(R3==1){
        lcd_data('0');
        while(R3==1);
    }
    
    C0=0,C1=0,C2=1;
    if(R0==1){
        lcd_data('3');
        while(R0==1);
    }
    if(R1==1){
        lcd_data('6');
        while(R1==1);
    }
    if(R2==1){
        lcd_data('9');
        while(R2==1);
    }
    if(R3==1){
        lcd_data('#');
        while(R3==1);
    }
}


void main(void) {
    TRISD=0;
    TRISC=0x00;
    TRISB=0xF0;
    lcd_initialize();
    lcd_command(0x80);
    lcd_string("..BY SSMK..",11);
    lcd_command(0xC0);
    while(1){
        keypad();
    }
    return;
}
