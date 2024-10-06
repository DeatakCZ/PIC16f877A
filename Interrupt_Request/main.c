/*
 * File:   newmain.c
 * Author: PanTalir
 *
 * Created on 12 June 2024, 14:12
 */

#define _XTAL_FREQ 4000000

#include "config.h"

#include <xc.h>


void __interrupt() ISR(void)
{
    if(INTF == 1)
    {
        RB2 = ~RB2;
        INTF = 0;
    }
}

void main(void) {
//IO set-up
    RB1 = 0;
    RB2 = 0;
    TRISB1 = 0;
    TRISB2 = 0;
    
//Interrupt set-up    
    INTEDG = 0;
    INTE = 1;
    GIE = 1;
    
    
    while(1){
        RB1 = 1;
        __delay_ms(1000);
        RB1 = 0;
        __delay_ms(1000);
    }
    
    
    
    
    
    return;
}
