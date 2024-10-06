/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 11 June 2024, 15:52
 */

//#define _XTAL_FREQ 4000000

#include <xc.h>
#include "config.h"


uint8_t TMR1_Counter = 0;
unsigned char Segment_Counter = 0;

void main(void) {
//Application set-up
    unsigned char segments_code[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    
//    Timer1 Size = 65.535
//    65.535-15.535 = 50.000
//    1s = 20 * 50.000[us]
    
    
    
//Timer1 Set-up
    TMR1 = 15535;
    T1CKPS1 = 0;
    T1CKPS0 = 0;
    T1OSCEN = 1;
    TMR1CS = 0;

    
//Interrupt set-up
    TMR1IE = 1;
    TMR1IF = 0;
    PEIE = 1;
    GIE = 1;
    
//Output set-up
    RB4 = 0;
    TRISB4 = 0;
    
    PORTD = 0x00;
    TRISD = 0x00;
    RA2 = 0;
    TRISA2 = 0;
    

    
//Application
    //while(1){}
    TMR1ON = 1;
    RA2 = 1;

    while (1){
        PORTD = segments_code[Segment_Counter];
        if(Segment_Counter>9){
            Segment_Counter = 0;
        }
    }
    
    return;
}


void __interrupt() ISR(void)
{
    if(TMR1IF)
    {
        TMR1_Counter++;
        if(TMR1_Counter == 20 )
        {
            RB4 = ~RB4;                 
            Segment_Counter++;
            TMR1_Counter = 0;    
        }
        TMR1 = 15535;
        TMR1IF = 0;
    }
}



