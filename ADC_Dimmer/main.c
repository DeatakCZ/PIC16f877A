/*
Lab Name            Analog Input ? Analog Output (LED Dimmer) ? ADC+PWM
Lab Number          21
Lab Level           Beginner
Lab Objectives      Learn how to configure The ADC Module and read analog signals. 
 *                  Combine the analog readings from a potentiometer with PWM to control LED brightness.
 */
#define _XTAL_FREQ 4000000

#include "config.h"
#include <xc.h>
#include <stdint.h>

//------[FUNCTIONS]-------------------------------------------
void PWM1_Init();
void PWM1_SetDuty(uint16_t);
void ADC_Init();
uint16_t ADC_Read(uint8_t);
//=============================================================
//-----[MAIN ROUTINE]------------------------------------------
void main(void) {
    PWM1_Init();
    ADC_Init();
    
    while(1)
    {
        PWM1_SetDuty(ADC_Read(0));  //Set PWM dutyCycle to AN0_Result
        __delay_ms(1);
    }
    return;
}
//------[END OF MAIN]--------------------------------------------
//==============================================================
//--------[CCP/PWM ROUTINE]-------------------------------------
void PWM1_Init()
{
//Configure CCP for PWM
    CCP1M3 = 1;
    CCP1M2 = 1;
    TRISC2 = 0;
//Set Frequency (5kHz)
    PR2 = 124;
//Set prescaler (1:4)
    T2CKPS0 = 1;
    T2CKPS1 = 0;
//Start the timer
    TMR2ON = 1;
}
void PWM1_SetDuty(uint16_t DC)
{
//Make sure value is within 10-bit range
    if(DC < 1024)
    {
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}
//------[AD CONVERTION ROUTIONES]---------------------------------
void ADC_Init()
{
//ADC ON, AN0channel, Clock /8
    ADCON0 = 0x41;
//8channels analog, rightJustified, Clock /8
    ADCON1 = 0x80;
}
uint16_t ADC_Read(uint8_t ANC)
{
//check channel validity
    if(ANC<0 || ANC>7)
        return 0;
    ADCON0 &= 0b11000101;
    ADCON0 |= ANC<<3;
    
    __delay_us(30);
    GO_DONE = 1;
    while(ADCON0bits.GO_DONE);
    return ((ADRESH<<7) + ADRESL);
}
//----------------------------------------------------------------
//===============================================================



