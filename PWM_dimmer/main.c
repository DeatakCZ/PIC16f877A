/*
 * Lab Name         PWM ? LED Dimmer
 * Lab Number       13
 * Lab Level        Beginner
 * Lab Objectives	Learn how to use CCP modules to generate PWM signals with a desired frequency of 2kHz
 * and variable duty cycle. 
 * We?ll use the output PWM signal to control the brightness of a small LED in this LAB. 
 * The duty cycle should be gradually increasing from 0 up-to 100% 
 * then it should start to gradually drop back to 0% and so on.
 */

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdbool.h>
#include "config.h"


void PWM1_Set_Duty(uint16_t);





void PWM1_Set_Duty(uint16_t DC)
{
    if(DC < 1024)
    {
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}

void main(void) {
    CCP1M3 = 1;
    CCP1M2 = 1;
    TRISC2 = 0;
    PR2 = 0;//124;
    
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    
    TMR2ON = 1;
    
    uint16_t DC = 0;
    bool Rise = 1;
    
    while(1)
    {
        DC = 0;
        
        while(DC<500)
        {
            PWM1_Set_Duty(DC);
            DC++;
            __delay_ms(1);
        }
        
        while(DC>0)
        {
            PWM1_Set_Duty(DC);
            DC--;
            __delay_ms(1);
        }
        
        __delay_ms(2);
        
        
        if(Rise)
            PR2++;
        else
            PR2--;
        
        if(PR2==255)
            Rise = 0;
        if(PR2==0)
            Rise = 1;
        
    }
    

    return;
}
