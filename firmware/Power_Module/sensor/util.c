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
<<<<<<< HEAD
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
=======
//void LED_Blink(void)
//{
//    // startup animation
//    LED0_SetHigh();
//    __delay_ms(100);
//    LED0_SetLow();
//    __delay_ms(100);
//    LED0_SetHigh();
//    __delay_ms(100);
//    LED0_SetLow();
//    __delay_ms(100);
//    LED0_SetHigh();
//    __delay_ms(100);
//    LED0_SetLow();
//    __delay_ms(500);
//    
//    LED1_SetHigh();
//    __delay_ms(100);
//    LED1_SetLow();
//    __delay_ms(100);
//    LED1_SetHigh();
//    __delay_ms(100);
//    LED1_SetLow();
//    __delay_ms(100);
//    LED1_SetHigh();
//    __delay_ms(100);
//    LED1_SetLow();
//}
>>>>>>> parent of 0c30394 (working)

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