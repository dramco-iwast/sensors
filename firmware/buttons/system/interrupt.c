#include <xc.h>
#include "interrupt.h"
#include "i2c1.h"

void DefaultSensorInterruptHandler(void);
void (* SensorInterruptHandler)(void) = &DefaultSensorInterruptHandler;

// main interrupt handler
void __interrupt() Interrupt_Handler(void){
    // handle sensor interrupt    
    SensorInterruptHandler();
    
    // handle I2C1 interrupt
    if(INTCONbits.PEIE == 1){
        // I2C1 interrupt
        if(PIE3bits.SSP1IE == 1 && PIR3bits.SSP1IF == 1){
            I2C1_ISR();
        } 
    }      
}

void SetSensorInterruptHandler(void (* InterruptHandler)(void)){
    SensorInterruptHandler = InterruptHandler;
}

void DefaultSensorInterruptHandler(void){
    return;
}
