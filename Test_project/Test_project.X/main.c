/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 02 June 2024, 22:45
 */



#include "config.h"
#include <xc.h>
//#include <pic16f877a.h>
#include <stdio.h>
#include <stdint.h>

#define _XTAL_FREQ 16000000

void main(void) 
{    

    TRISD = 0x00;
    PORTD = 0xFF;
        
    RC0 = 0;
    RC1 = 1;
    TRISC0 = 0;
    TRISC1 = 0;
    
    
    
    __delay_ms(200);

    RC0 = 1;
    RC1 = 0;
    PORTD = 0x00;
    
    __delay_ms(200);
    
    while(1)
    {
    PORTD = 0x01;    
    RC0 = ~RC0;
    RC1 = ~RC1;
        for( uint8_t i = 0 ; i < 8 ; i++ )
        {   
            __delay_ms(500);
            PORTD = PORTD << 1; 
            
        }
    __delay_ms(2000);
    }
    
    

    
    
    return;
}
