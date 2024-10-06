/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 11 June 2024, 14:04
 */
#define _XTAL_FREQ 4000000

#include <xc.h>
#include "config.h"

void main(void) {
    //Blink LED to test function
    RB4 = 0;
    TRISB4 = 0;
   
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    return;
}


void __interrupt() ISR(void)
{
    
    if(ADIF == 1){
        
    }
    
    if(EEIF == 1){
        
    }
    
}