/*
 * File:   mian.c
 * Author: PanTalir
 *
 * Created on 14 June 2024, 14:02
 */
#define _XTAL_FREQ 4000000

#include <xc.h>

#include "config.h"



void main(void) {
    
    // 4000000 /s
    // 0.25us per F_osc
    // 8*T_osc = 0.2us => T_ad > 1,6us
    // review table for correct settings
    
    uint16_t Data = 0;
    
    
//ADC SET-UP
    ADCON0 = 0x41;      //ADCON =1, AN0 channel selected, ADC Clock = F_osc/8
    ADCON1 = 0x80;      //8ANalog channels, RightJustified, ADC Clock = F_osc/8
    
//INTERRUPTS SET-UP    
    ADIF = 0;
//    ADIE = 1;
//    PEIE = 1;
//    GIE = 1;
    
    __delay_us(30);
    while(1)
    {
        while(GO_DONE);
        Data = (ADRESH << 8) + ADRESL;
        __delay_us_(10);
        GO_DONE = 1;
        
    
    
    }
    return;
}
