/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 16 June 2024, 17:19
 */
#include "config.h"

#include <xc.h>
#include <stdint.h>
#include <stdio.h>


#define _XTAL_FREQ 16000000
#define PIN_AnalogIN RA0                //Analog  Input
#define PIN_4021_DataIN RB0              //Digital Input
#define PIN_4021_Clock RB1               //Digital Output
#define PIN_4021_Latch RB2               //Digital Output
#define PIN_4022_Clock RB3              //Digital Output
#define PIN_4022_Reset RB4              //Digital Output

uint8_t readMatrix();





uint8_t readMatrix()
{
    uint8_t data = 0x0;
//Load data into register
    PIN_4021_Latch = 1;
    __delay_us(4);
    PIN_4021_Latch = 0;
//Save data into variable
    for(int i = 0 ; i < 8 ; i++)
    {
        PIN_4021_Clock = 0;
        __delay_us(4);
        data = ( data << 1 );
        if(PIN_4021_DataIN)
        {
            data = data | 0x1;
        }
        PIN_4021_Clock = 1;
        __delay_us(4);
    }
    return data;
}



void main(void) {
    
//------------SET_UP-------------------------------------------
//Debug 
    RC0 = 0;
    RC1 = 0;
    TRISC0 = 0;
    TRISC1 = 0;
    
    //TRISA0 = 1;

//PORTB - Control IO
    PIN_4021_Clock = 1;
    PIN_4021_Latch = 0;
    PIN_4022_Clock = 0;
    PIN_4022_Reset = 0;
    TRISB = 0x01;
    
//PORTD - Debug visual output    
    PORTD = 0x00;
    TRISD = 0x00;
    
//VARIABLES    
    uint8_t data = 0;
   
//--------------------One-time code----------------------------------    
    PORTD = 0xFF;
    __delay_ms(1000);
    PORTD = 0x00;
    __delay_ms(500);
    
//-------------------Reset Control IC's------------------------------
    PIN_4022_Reset = 1;
    for(uint8_t i = 0 ; i < 8 ; i++ )
    {
        PIN_4021_Clock = 0;
        __delay_us(4);
        PIN_4021_Clock = 1;
    }
    PIN_4022_Reset = 0;
//===================MAIN LOOP====================================            
    while(1)
    {

//Read Matrix status into 8-bit variable, then look at next segment        
        for( uint8_t i = 0 ; i < 4 ; i++ )
        {
            RC0 = 1;
            
            data = readMatrix();
            PORTD = 0x00 | data;
            
            PIN_4022_Clock = 1;
            __delay_us(4);
            PIN_4022_Clock = 0;
            __delay_us(4);
        
            RC0 = 0;
            __delay_ms(20);
        }
        
        RC1 = 1;
        PORTD = 0x00;
//Quickly toggle through unused Outputs
/*      
        for( uint8_t i = 0 ; i < 4 ; i++ )
        {
            PIN_4022_Clock = 1;
            __delay_us(4);
            PIN_4022_Clock = 0;
            __delay_us(4);
        }
*/
       PIN_4022_Reset = 1;
        __delay_us(4);
        PIN_4022_Reset = 0;
        __delay_us(4);
//Cycle delay
        __delay_ms(8);
        RC1 = 0;
    }
    return;
}
