/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 13 June 2024, 15:25
 */

#define _XTAL_FREQ 4000000

#include <xc.h>
#include "config.h"


void PWM1_DutyCycle(uint16_t DC);
void DC_Reverse();
void DC_Start();
void DC_Stop();

void PWM1_DutyCycle(uint16_t DC)
{
    CCP1X  = (DC) &  1;    // Get bit 0  LSB
    CCP1Y  = (DC) &  2;    // Get bit 1  (bitwise AND)
    CCPR1L = (DC) >> 2;    // Move Duty Cycle 2 bits over and assign it to register
}

void DC_Reverse()
{
    RD0 = ~RD0;
    RD1 = ~RD1;
    RD2 = ~RD2;
    RD3 = ~RD3;
}



void DC_Start()
{
    PORTD = 0x0A;
}

void DC_Stop()
{
    PORTD = 0x00;
}

void main(void) {
    
//TIMER2 SET-UP
    TOUTPS3 = 0;
    TOUTPS2 = 0; 
    TOUTPS1 = 0;
    TOUTPS0 = 0;
    TMR2ON  = 0;
    T2CKPS1 = 0;
    T2CKPS0 = 1;
    TMR2 = 0;
    
//CCP1 SET-UP
    CCP1M3 = 1; 
    CCP1M2 = 1;
   
/*
// FREQUENCY CALCULATIONS    
// f_PWM = 2kHz
//
//      1         1
// T = --- ; f = ---   
//      f         T  
//    
// T_pwm =  (PR2 + 1) * 4 * T_osc * TMR2_PreScaler
//    
//   1                          1
// ------ = (PR2 + 1) * 4 * --------- * 1  
//  2000                    4.000.000 
//    
//        4.000.000
// PR2 = ----------- - 1 = 500 - 1 = 499   
//          8.000
//    
// Size of PR2 is 8-bits => 499 > 255
// Different prescaler has to be selected
//                                     \/
//    1                        1
// ------ = (PR2 + 1) * 4 ----------- * 4    
//  2000                   4.000.000 
//        
//        4.000.000    
// PR2 = ------------ - 1 = 124 
//          32.000
//    
// PR2 = 124   
//    
//    
//    
//    
//    
// DUTY CYCLE CALCULATIONS:       7     3     7     3  
// For 70% Duty cycle   =>  _|-------|___|-------|___   
//    
//                   1
// T_pwm = 0,70 * ------ = 0,000.35 s 
//                 2000
//    
// T_pwm = (CCR1L:CCP1CON<5:4>) * T_osc * TMR2_PreScaler   
//    
//                                T_pwm
// (CCR1L:CCP1CON<5:4>) = -----------------------    
//                         T_osc * TMR2_PreScaler
//    
//                            0,000.35             0,35          0,35
// (CCR1L:CCP1CON<5:4>) = ------------------ = -------------- = ------ = 350   
//                         0,000.000.25 * 4     0,000.25 * 4     0,001
//    
//  70% Duty cycle == [ 350 >> (CCR1L:CCP1CON<5:4>) ]    
//    
// 100% Duty cycle == [ 500 >> (CCR1L:CCP1CON<5:4>) ] 
*/

// PWM SET-UP
    PR2 = 124;
    
//IO SET-UP
    TRISC2 = 0;
        
    TRISB = 0xFF;
    //TRISA5 = 1 ; 
    
    PORTD = 0x00;
    TRISD = 0x00;

//INTERRUPT SET-UP
    GIE = 1;
    PEIE = 1;
    

    PWM1_DutyCycle(250);
    TMR2ON = 1;
    
    while(1)
    {
        if(!RB3)
            PWM1_DutyCycle(500);    //100%
        if(!RB4)
            PWM1_DutyCycle(250);    //75%
        if(!RB5)
            PWM1_DutyCycle(0);    //50%
//        if(!RA5)
//            PWM1_DutyCycle(0);      //0%
        if(!RB0)
            DC_Reverse();
        if(!RB2)
            DC_Start();
        if(!RB1)
            DC_Stop();
    
    
    __delay_ms(100);
    }
    
    return;
}
