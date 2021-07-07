#include <xc.h>
#include "interrupt.h"
#include "i2c1.h"
<<<<<<< HEAD
//#include "i2c2.h"
=======
#include "i2c2.h"
>>>>>>> parent of 0c30394 (working)
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
<<<<<<< HEAD
//        else if(PIE3bits.BCL2IE == 1 && PIR3bits.BCL2IF == 1)
//        {
//            I2C2_BusCollisionISR();
//        }
//        else if(PIE3bits.SSP2IE == 1 && PIR3bits.SSP2IF == 1)
//        {
//            I2C2_ISR();
//        } 
=======
        else if(PIE3bits.BCL2IE == 1 && PIR3bits.BCL2IF == 1)
        {
            I2C2_BusCollisionISR();
        }
        else if(PIE3bits.SSP2IE == 1 && PIR3bits.SSP2IF == 1)
        {
            I2C2_ISR();
        } 
>>>>>>> parent of 0c30394 (working)
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
