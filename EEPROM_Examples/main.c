/*
 * Lab Name         Internal EEPROM
 * Lab Number       15
 * Lab Level        Beginner
 * Lab Objectives	Learn how to use the internal EEPROM Memory to write/read data. 
 *                  Develop the necessary firmware in order to store some variables in the EEPROM memory. 
 *                  Then retrieve them back after a hardware restart for the microcontroller chip. 
 *                  Everything is done with some push buttons and LEDs.
 */
#define READ RB3
#define W_3 RB0
#define W_5 RB1
#define W_7 RB2

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdint.h>

#include "config.h"




void Write(uint8_t Address, uint8_t Data);
uint8_t Read(uint8_t Address);

void Write(uint8_t Address, uint8_t Data)
{
    uint8_t GIE_State = 0;
    while(EECON1bits.WR);       // Wait until end of last cycle
    EEADR = Address;            // Set EEPROM address
    EEDATA = Data;              // Set Data to write
    EECON1bits.EEPGD = 0;       // Set to write to data memory instead of program memory
    EECON1bits.WREN = 1;        // Enable operation
    GIE_State = INTCONbits.GIE; // Save Interrupt settings
    INTCONbits.GIE = 0;         // Disable interrupts
    EECON2 = 0x55;              // -
    EECON2 = 0xAA;              // |Writting sequence
    EECON1bits.WR = 1;          // -
    INTCONbits.GIE = GIE_State;         // Reload interrupt setting
    EECON1bits.WREN = 0;        // Disable operation
    EECON1bits.WR = 0;          // Set ready for next operation
}

uint8_t Read(uint8_t Address)
{
    uint8_t Data;               // 
    EEADR = Address;            // Set read address
    EECON1bits.EEPGD = 0;       // set target as data memory instead of program memory
    EECON1bits.RD = 1;          // Set read operation
    Data = EEDATA;              // Read the data into variable
    return Data;                // 
}


void main(void) {
    
//IO SET-UP
    TRISB = 0x0F;
    PORTD = 0x00;
    TRISD = 0x00;
    
    uint8_t CurAddr = 0x00;
    
    
    while(1)
    {
        if(!W_3)
        {
            Write(CurAddr, 3);
            CurAddr++;
            __delay_ms(500);
        }
        if(!W_5)
        {
            Write(CurAddr, 5);
            CurAddr++;
            __delay_ms(500);
        }
        if(!W_7)
        {
            Write(CurAddr, 7);
            CurAddr++;
            __delay_ms(500);
        }
        if(!READ)
        {
            CurAddr = 0x00;
            
            while(CurAddr != 0x03)
            {
                
                PORTD = Read(CurAddr);
                CurAddr++;
                __delay_ms(1500);
                PORTD = 0x00;
                __delay_ms(500);
            }
            CurAddr = 0x00;
        }
    }
    
    
    
    
    
    
    
    
    
    
    return;
}
