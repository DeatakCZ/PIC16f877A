/*
 * Lab Name         CCP-CompareMode
 * Lab Number       12
 * Lab Level        Intermediate
 * Lab Objectives	Learn how to use the CCP module in compare mode
 *                  in order to generate accurate time intervals utilizing the Timer1 hardware as a resource. 
 *                  We?ll generate a 0.5s time interval to blink an LED in this LAB.
 */


#include <xc.h>
#include "config.h"

#define _XTAL_FREQ 4000000

uint8_t C = 0;

void __interrupt() ISR(void)
{
    if(CCP1IF)
    {
        C++;
        if(C==10)
        {
            RB0 = ~RB0;
            C = 0;
        }
        CCP1IF = 0;
    }
}

void main(void) {
//Timer1 set-up    
    TMR1ON = 0;
    TMR1 = 0;
    T1CKPS1 = 0;
    T1CKPS0 = 0;
    T1OSCEN = 1;
    T1SYNC = 0;
    TMR1CS = 0;
    TMR1ON = 0;

    
//CCP1 Set-up
    CCP1X = 0;
    CCP1Y = 0;
    CCP1M3 = 1;
    CCP1M2 = 0;
    CCP1M1 = 1;
    CCP1M0 = 1;
  
//Timer1 is compared with this    
    CCPR1 = 50000;      // 0,5s because of Prescaler 1:8 , 
                        // 4MHz crystal => 4.000.000 Instructions per second
                        // PIC16F877A 4 Clock cycles per 1 Instruction cycles 
                        // 1.000.000 Instruction cycles per 1 second 
                        // 1.000.000 / 2 = 500.000 cycles per 0,5 second     
                        //   500.000 / 8 =  62.500 cycles per 0,5 second after prescaler
                        //    62.500 => When TMR1 is same 0,5 seconds elapsed
    
//Interrupts set=up
    GIE = 1;
    PEIE = 1;
    CCP1IE = 1;

//IO Set-up
    RB0 = 0;
    TRISB0 = 0;
    TRISC2 = 0;

    
//Timer1 Start
    TMR1ON = 1;
    while(1)
    {
    }
    
    return;
}
