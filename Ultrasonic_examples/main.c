/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 12 June 2024, 10:30
 */
#define _XTAL_FREQ 4000000

#define trigger RC2
#define echo RC3

#include "config.h"
#include <xc.h>

int calc_distance(void);

uint8_t C = 0;
_Bool Error = 0;

//              4 * PreScale(1)            4                 TMR1
//Time = TMR1 * ---------------- = TMR1 * ------------  = -------------
//                   Fosc                  4.000.000       1.000.000
//
//
//
//                                                  TMR1        1           340 * TMR1      TMR1            TMR1           TMR1
//Distance = (time/2) * speed = (Time/2) * 340 = ----------- * --- * 340 = ------------- = --------- [m] = ----------  = --------[cm]
//                                                1.000.000     2            2.000.000      5882,353       58,823.53       58,82
int calc_distance(void)
{
//Initialization 
    int distance = 0;
    TMR1ON = 0;
    TMR1 = 0; 
    TMR2ON = 0;
    TMR2 = 0x00;
    C = 0;
    
//send out >10uS pulse    
    trigger = 1;
    __delay_us(10);
    trigger = 0;
    
//safety timer for no response situations   
    TMR2ON = 1;

//wait for return of pulse   
    while(!echo && !Error);
    TMR1ON = 1;
    if(Error)
    {
        TMR1ON = 0;
        TMR2ON = 0;
        Error = 0;
        return -1;
    }
    
//wait for pulse to end to stop timer to calculate pulse width    
    while(echo && !Error);
    TMR1ON = 0;
    TMR2ON = 0;
    if(Error)
    {
        Error = 0;
        return -1;
    }
    
//Calculate distance    
    distance = TMR1 / 58.82;
    
    return distance;
}


void __interrupt() ISR(void)
{
    if(TMR2IF)
    {
        C++;
        //      8000uS per timer2  == 8ms == 0,008 seconds
        //      125 * 0.008 = 1  [ s]
        //      7   * 0.008 = 56 [ms]
        if(C == 7 )
        {
            Error = 1;
            C = 0;
        }
        TMR2IF = 0;
    }
}

void main(void) {
    
//IO set-up
    PORTB = 0x00;
    TRISB = 0x00;
    
    RC2 = 0;
    TRISC2 = 0;
    TRISC3 = 1;
    RD0 = 0;
    TRISD0 = 0;
    
    PORTB = 0xFF;
    __delay_ms(1000);
    PORTB = 0x00;
    
//Timer1 set-up
    TMR1 = 0;
    TMR1CS = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
//Timer2 set-up
    PR2 = 0xFA;             //250
    TMR2 = 0;
    TMR2ON = 0;
    TOUTPS0 = 1;
    TOUTPS1 = 1;
    TOUTPS2 = 1;
    TOUTPS3 = 1;
    T2CKPS0 = 1;
    T2CKPS1 = 1;
    
//Interrupts
    GIE = 1;
    PEIE = 1;
    TMR2IE = 1;
    
//Application set-up
    int dist = 0;
    
    while(1)
    {
       
       dist = calc_distance()/20;
       switch(dist)
       {
           case 0: { PORTB = 0x00; __delay_ms(50); break;} 
           case 1: { PORTB = 0x01; __delay_ms(50); break;} 
           case 2: { PORTB = 0x03; __delay_ms(50); break;}
           case 3: { PORTB = 0x07; __delay_ms(50); break;}
           case 4: { PORTB = 0x0F; __delay_ms(50); break;}
           case 5: { PORTB = 0x1F; __delay_ms(50); break;} 
           case 6: { PORTB = 0x3F; __delay_ms(50); break;}
           case 7: { PORTB = 0x7F; __delay_ms(50); break;}
           case 8: { PORTB = 0xFF; __delay_ms(50); break;}
           default:{ PORTB = 0x00; __delay_ms(50); break;}
        }
        __delay_ms(60);
        
        RD0 = ~RD0;
        
        
        /*
        dist = calc_distance()/5;
        if(dist==1)
        {PORTB = 0x01; __delay_ms(50);}
        if(dist==2)
        {PORTB = 0x03; __delay_ms(50);}
        if(dist==3)
        {PORTB = 0x07; __delay_ms(50);}
        if(dist==4)
        {PORTB = 0x0F; __delay_ms(50);}
        else
        {PORTB = 0x00; __delay_ms(50);}
        */
        
        /*
        dist = calc_distance();
        if(dist != 0)
        {
            PORTB = 0xFF;
        }
        __delay_ms(500);
        */
    }
    
    return;
}
