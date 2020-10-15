/*  ____  ____      _    __  __  ____ ___
 * |  _ \|  _ \    / \  |  \/  |/ ___/ _ \
 * | | | | |_) |  / _ \ | |\/| | |  | | | |
 * | |_| |  _ <  / ___ \| |  | | |__| |_| |
 * |____/|_| \_\/_/   \_\_|  |_|\____\___/
 *                           research group
 *                             dramco.be/
 *
 *  KU Leuven - Technology Campus Gent,
 *  Gebroeders De Smetstraat 1,
 *  B-9000 Gent, Belgium
 *
 *         File: system.c
 *      Created: 2020-10-02
 *       Author: Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Basic system initialization
 * 
 */

#include "system.h"


void SYSTEM_Initialize(uint8_t slave_address) //MODIFIED (was void))
{
    PMD_Initialize();
    OSCILLATOR_Initialize();
    
    VREGCONbits.VREGPM = 1; // Low-Power Sleep mode enabled in Sleep
    //Unused I/O pins should be configured as outputs and driven to a logic
    //low state. Alternatively, connect a1k? to 10 k? resistor to VSS on unused
    // pins to drive the output to logic low
    
    // added from geoffrey code
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    ANSELCbits.ANSC1 = 1; // set RC1 to analog mode
    
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISCbits.TRISC1 = 1; // set input for ADC pin
    
    LATA = 0xFF;
    LATB = 0xFF;
    LATC = 0xFF;
    LATCbits.LATC1 = 0; // set low input for ADC pin
    
    I2C1_Initialize(slave_address);
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
}

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // HFFRQ 32_MHz; 
    OSCFRQ = 0x06;
}

void PMD_Initialize(void)
{
    // disable everything by default -> should be enabled by sensor
    PMD0 = 0xFF;
    PMD0bits.SYSCMD = 0; // enabled clocks to peripherals
    
    PMD1 = 0xFF;
    PMD2 = 0xFF;
    PMD3 = 0xFF;
    PMD4 = 0xFF;
    PMD5 = 0xFF;
    PMD6 = 0xFF;
    PMD7 = 0xFF;
}

/**
 End of File
*/
