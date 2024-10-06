/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 03 June 2024, 15:35
 */
#define _XTAL_FREQ 4000000

#include "config.h"
#include <xc.h>



void main(void) {
                                      //0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6  
    unsigned char segments_code[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    unsigned char counter = 0;
    PORTD = 0x00;
    TRISD = 0x00;
    RA2 = 0;
    TRISA2 = 0;
    
    RA2 = 1;
    while (1){
        PORTD = segments_code[counter];
        __delay_ms(1000);
        counter++;
        if(counter>9){
            counter = 0;

        }
    }
    
    
    
    return;
}
