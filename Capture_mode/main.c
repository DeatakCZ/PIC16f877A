/*
 * Lab Name         CCP CaptureMode
 * Lab Number       11
 * Lab Level        Introductory
 * Lab Objectives	Learn how to use the CCP module in CaptureMode. 
 *                  Run the Timer1 module in synchronized counter mode and increment its value with an external push button input pulses. 
 *                  When the RC2/CCP1 pin is driven-high (Rising edge), the TMR1 counts should be PORTed out to an IO port hooked to some LEDs.
 */

#define _XTAL_FREQ 4000000

#include "config.h"

#include <xc.h>


void __interrupt() ISR(void)
{
    if(CCP1IF)
    {
        PORTD = CCPR1;
        CCP1IF = 0;
    }
}


void main(void) {
//Timer1 set-up    
    TMR1 = 0;
    T1CKPS1 = 0;
    T1CKPS0 = 0;
    T1OSCEN = 1;
    T1SYNC = 0;
    TMR1CS = 1;
    TMR1ON = 1;

    
//CCP1 Set-up
    CCP1X = 0;
    CCP1Y = 0;
    CCP1M3 = 0;
    CCP1M2 = 1;
    CCP1M1 = 0;
    CCP1M0 = 1;
    
//Interrupts    
    GIE = 1;
    PEIE = 1;
    CCP1IE = 1;
    
//IO Set-up
    PORTD = 0x00;       //Output, LED display Captured
    TRISD = 0x00;
    PORTB = 0x00;       //Output, LED display Actual
    TRISB = 0x00;
    
    TRISC2 = 1;         //Input, output amount to LEDs
    TRISC0 = 1;         //Input, add to counter
    
    
    while(1)
    {

        PORTB = TMR1;
    }
    
    
    return;
}
