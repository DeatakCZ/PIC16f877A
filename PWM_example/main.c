/*
 * File:   main.c
 * Author: PanTalir
 *
 * Created on 13 June 2024, 09:28
 */


#include <xc.h>
#include "config.h"

#define __XTAL_FREQ 4000000;

void main(void) {

// CCP1 PWM Set-up    
    CCP1M3 = 1;
    CCP1M2 = 1;

// IO set-up
    TRISC2 = 0;// Pin RC2/CCP1, CCPx pin must be set as output for PWM to work
    
    
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
  
// Timer2 set-up
    PR2 = 124;
    TOUTPS3 = 0;    //PostScale
    TOUTPS2 = 0;
    TOUTPS1 = 0;
    TOUTPS0 = 0;
    TMR2ON  = 0;
    T2CKPS1 = 0;    //PreScale
    T2CKPS0 = 1;
    
    
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
//
    
    CCP1X  = (250) &  1;    // Get bit 0  LSB
    CCP1Y  = (250) &  2;    // Get bit 1  (bitwise AND)
    CCPR1L = (250) >> 2;    // Move 350 2 bits over and assign it to register
    
    TMR2ON = 1;
    
    
    while(1)
    {
        
    }
    
    return;
}
