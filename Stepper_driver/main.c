/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 03 June 2024, 17:38
 */

#define _XTAL_FREQ 4000000  //[Hz]
#define STEP 25            //[ms]

#include "config.h"
#include <xc.h>

void main(void) {
    
    PORTB = 0x00;
    TRISB = 0x00;
    
    TRISC0 = 1;
    TRISC1 = 1;
    
    //              STATES:     0x01, 0x02, 0x04, 0x08
    //                          0001, 0010, 0100, 1000
    
    //unsigned char coils[4] = { 0x01, 0x02, 0x04, 0x08 };
    unsigned char i = 0;
    
    while(1){
        while(RC0){
            for(int j=0; j<4; j++){
                PORTB = (1<<i);
                __delay_ms(STEP);
                i++;
                if(i==4)
                    i = 0;
            }
        }
    
        while(RC1){
            for(int j=0; j<4; j++){
                PORTB = (8>>i);
                __delay_ms(STEP);
                i++;
                if(i==4)
                    i = 0;
            }
        }
    }
    
    
    return;
}
