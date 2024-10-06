/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 04 June 2024, 14:37
 */

#define _XTAL_FREQ 4000000


#include "config.h"
#include <xc.h>

void main(void) {

    CCP1IE = 1;     //CCP1 Interrupt enable
    PEIE = 1;       //Peripheral Interrupts enable
    GIE = 1;        //General Interrupts enable
    

    return;
}


void __interrupt() ISR(void)
{
    if(CCP1IF)              //CCP1 Flag
    {
        //Code
        CCP1IF = 0;         //Always disable after Interrupt handler!
    }
}