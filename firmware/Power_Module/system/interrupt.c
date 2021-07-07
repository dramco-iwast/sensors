#include <xc.h>
#include "interrupt.h"
#include "i2c1.h"
#include "adcc.h"

void DefaultSensorInterruptHandler(void);
void (* SensorInterruptHandler)(void) = &DefaultSensorInterruptHandler;

// main interrupt handler
void __interrupt() Interrupt_Handler (void)
{
    
    // handle sensor interrupt    
    SensorInterruptHandler();
    
    
    // interrupt handler
//    if(PIE0bits.IOCIE == 1 && PIR0bits.IOCIF == 1)
//    {
//        PIN_MANAGER_IOC();
//    }
    if(INTCONbits.PEIE == 1)
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

void SetSensorInterruptHandler(void (* InterruptHandler)(void)){
    SensorInterruptHandler = InterruptHandler;
}

void DefaultSensorInterruptHandler(void){
    return;
}
