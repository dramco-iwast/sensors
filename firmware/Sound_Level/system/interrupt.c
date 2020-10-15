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
 *         File: interrupt.c
 *      Created: 2020-10-15
 *       Author: Mathias Alleman - Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Interrupt functionality
 *
 */

#include "interrupt.h"
#include "system.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.IOCIE == 1 && PIR0bits.IOCIF == 1)
    {
        PIN_MANAGER_IOC();
    }
    else if(INTCONbits.PEIE == 1)
    {
        if(PIE3bits.SSP1IE == 1 && PIR3bits.SSP1IF == 1)
        {
            I2C1_ISR();
        } 
        else if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
        {
            ADCC_ISR();
        } 
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/
