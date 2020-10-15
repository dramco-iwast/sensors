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
 *         File: pin_manager.c
 *      Created: 2020-10-15
 *       Author: Mathias Alleman - Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Pin manager
 *
 */

#include "pin_manager.h"

void (*IOCCF0_InterruptHandler)(void);
void (*IOCCF2_InterruptHandler)(void);
void (*IOCCF4_InterruptHandler)(void);
void (*IOCCF6_InterruptHandler)(void);

  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCCF0
    if(IOCCFbits.IOCCF0 == 1)
    {
        IOCCF0_ISR();  
    }	
	// interrupt on change for pin IOCCF2
    if(IOCCFbits.IOCCF2 == 1)
    {
        IOCCF2_ISR();  
    }	
	// interrupt on change for pin IOCCF4
    if(IOCCFbits.IOCCF4 == 1)
    {
        IOCCF4_ISR();  
    }	
	// interrupt on change for pin IOCCF6
    if(IOCCFbits.IOCCF6 == 1)
    {
        IOCCF6_ISR();  
    }	
}

/**
   IOCCF0 Interrupt Service Routine
*/
void IOCCF0_ISR(void) {

    // Add custom IOCCF0 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF0_InterruptHandler)
    {
        IOCCF0_InterruptHandler();
    }
    IOCCFbits.IOCCF0 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF0 at application runtime
*/
void IOCCF0_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF0_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF0
*/
void IOCCF0_DefaultInterruptHandler(void){
    // add your IOCCF0 interrupt custom code
    // or set custom function using IOCCF0_SetInterruptHandler()
}

/**
   IOCCF2 Interrupt Service Routine
*/
void IOCCF2_ISR(void) {

    // Add custom IOCCF2 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF2_InterruptHandler)
    {
        IOCCF2_InterruptHandler();
    }
    IOCCFbits.IOCCF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF2 at application runtime
*/
void IOCCF2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF2
*/
void IOCCF2_DefaultInterruptHandler(void){
    // add your IOCCF2 interrupt custom code
    // or set custom function using IOCCF2_SetInterruptHandler()
}

/**
   IOCCF4 Interrupt Service Routine
*/
void IOCCF4_ISR(void) {

    // Add custom IOCCF4 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF4_InterruptHandler)
    {
        IOCCF4_InterruptHandler();
    }
    IOCCFbits.IOCCF4 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF4 at application runtime
*/
void IOCCF4_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF4_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF4
*/
void IOCCF4_DefaultInterruptHandler(void){
    // add your IOCCF4 interrupt custom code
    // or set custom function using IOCCF4_SetInterruptHandler()
}

/**
   IOCCF6 Interrupt Service Routine
*/
void IOCCF6_ISR(void) {

    // Add custom IOCCF6 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF6_InterruptHandler)
    {
        IOCCF6_InterruptHandler();
    }
    IOCCFbits.IOCCF6 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF6 at application runtime
*/
void IOCCF6_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF6_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF6
*/
void IOCCF6_DefaultInterruptHandler(void){
    // add your IOCCF6 interrupt custom code
    // or set custom function using IOCCF6_SetInterruptHandler()
}

/**
 End of File
*/

