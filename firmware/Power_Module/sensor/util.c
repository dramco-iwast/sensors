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
 *         File: util.c
 *      Created: 2020-11-27
 *       Author: Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Utilities - LEDS - Interrupt pin
 *
 */

#include "util.h"


void LED_Init(void)
{
    LED0_SetDigitalMode();
    LED0_SetDigitalOutput();
    LED0_SetLow();
    
    LED1_SetDigitalOutput();
    LED1_SetDigitalMode();
    LED1_SetLow();
    
    /* Blink LED */
    LED_Blink();  
}

/* Animation when Sound Module is plugged in */
void LED_Blink(void)
{
    // startup animation
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(100);
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(100);
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(500);
    
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
    __delay_ms(100);
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
    __delay_ms(100);
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
}

void comm_init(void)
{
    READY_SetDigitalMode();
    READY_SetDigitalOutput();
    READY_SetHigh();
}

void generateInt(void){
    READY_SetLow();
    __delay_ms(1);                          
    READY_SetHigh();
}

void WDT_set_16sec()
{
    WDTCON0 = 0x1C; // 16 second period
}

void WDT_set_64sec()
{
    WDTCON0 = 0x20; // 64 second period
}

void WDT_Init(void)
{
    // initialize timer for periodic measurements   
    WDT_set_64sec();
    WDTCON1 = 0x07; // LFINTOSC, window 100%
    
    // Enable watchdog
    WDTCON0bits.SEN = 0;
    CLRWDT();
    WDTCON0bits.SEN = 1;
}

void Enter_sleep(){
    /* Go to sleep */
    CPUDOZEbits.IDLEN = 0; // make sure PIC is not in doze mode before going to sleep   
    NOP();
    SLEEP(); // enter sleep
    NOP();
    NOP();
}
