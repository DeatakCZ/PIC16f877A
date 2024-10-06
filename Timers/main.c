/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 11 June 2024, 15:13
 */
#define _XTAL_FREQ 4000000

#include <xc.h>
#include "config.h"

uint8_t C = 0;
    

void main(void) {
    
    // -- [[ Configure Timer1 To Operate In Timer Mode  ]] --

    // Clear The Timer1 Register. To start counting from 0
    TMR1 = 0;
    
    // Choose the local clock source (timer mode)
    TMR1CS = 0;
    
    // Choose the desired prescaler ratio (1:1)
    T1CKPS0 = 0;
    T1CKPS1 = 0;
            
    // Switch ON Timer1 Module!
    TMR1ON = 1;
    
    // Enable Timer1 Interrupt way
    TMR1IE = 1;     //TMR1 Interrupt
    PEIE = 1;       //Peripheral Interrupt
    GIE = 1;        //Global Interrupt
    

    
    
//    Tick Time = 1 / ( F_osc / 4 )           F_osc = F_clk
//           TT = 1 / (4.000.000 / 4 )
//           TT = 1 / 1.000.000
//    Tick Time = 1 us [microsecond]
//           TT = 0,000.001 s 
// 
//    
//    Time = ( 4 * Prescaler * (65536-TMR1) * TimerSize ) / F_osc
//    
//    Timer 1 size = 16-bit = 65535 => # of Ticks(Clocks) before TMR1 overflow
//    T_overflow = # of Ticks * TickTime
//    T_overflow = 65535 * 0,000.001 
//    T_overflow = 0.065535 s 
//    T_overflow =~ 65 ms
    
    
    return ;
}
    
void __interrupt() ISR(void)
{
    if(TMR1IF){
        C++;
        if(C==3)
        {
            //time trigger
        }
        TMR1IF = 0;
    }



}


