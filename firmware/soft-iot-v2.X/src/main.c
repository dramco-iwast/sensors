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
 *         File: main.c
 *      Created: 2019-09-11
 *       Author: Geoffrey Ottoy
 *      Version: major.minor
 *
 *  Description: Generic I2C sensor interface for 
 *                  "IoT with a SOFT touch"
 *               (DRAMCO / KU Leuven TCG project)
 *
 */

#include <stdio.h>
#include <string.h>
#include "../hal/mcc.h"

// include sensor
#include "../sensors/dummy.h"

#ifndef TYPE_BYTE
    #error "TYPE_BYTE is not defined"
#elif (~(~TYPE_BYTE + 0) == 0 && ~(~TYPE_BYTE + 1) == 1)
    #error "TYPE_BYTE is defined, but has no value"
#endif

#ifndef LENGTH_BYTE
    #error "LENGTH_BYTE is not defined"
#elif (~(~LENGTH_BYTE + 0) == 0 && ~(~LENGTH_BYTE + 1) == 1)
    #error "LENGTH_BYTE is defined, but has no value"
#endif

#ifndef SLAVE_ADDRESS
    #error "SLAVE_ADDRESS is not defined"
#elif (~(~SLAVE_ADDRESS + 0) == 0 && ~(~SLAVE_ADDRESS + 1) == 1)
    #error "SLAVE_ADDRESS is defined, but has no value"
#endif

extern uint8_t measurementData[];

bool ledState = 0;
bool startMeasurement = 0;

void ToggleLed(void){
    if(ledState){
        LATAbits.LATA2 = 0;
    }
    else{
        LATAbits.LATA2 = 1;
    }
    ledState = (bool)!ledState;
    printf("led toggled\n\0");
}

/* Main behavior
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize(SLAVE_ADDRESS);

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    // Custom button press interrupt
    IOCCF2_SetInterruptHandler(ToggleLed);

    printf("uart test\n\0");

    while (1){
        // I2C Slave operation (respond to commands)
        if(I2C1_CommandReceived()){
            uint8_t cmd;
            uint8_t len;
            uint8_t data[20];
            I2C1_GetCommand(&cmd, data, &len);
            
            switch(cmd){
                // POLL
                case 0x10:{ // master polls address -> respond with ack
                    uint8_t ack = 0xAA;
                    I2C1_SetTransmitData(&ack, 1);
                } break;
                // TYPE
                case 0x11:{ // master requests sensor type -> respond with type
                    uint8_t type = TYPE_BYTE;
                    I2C1_SetTransmitData(&type, 1);
                } break;
                // LENGTH
                case 0x12:{ // master requests measurement data length -> respond with length
                    uint8_t dlen = LENGTH_BYTE;
                    I2C1_SetTransmitData(&dlen, 1);
                } break;
                // MEASURE
                case 0x13:{ // master forces measurement -> respond with ack
                    uint8_t ack = 0xAA;
                    I2C1_SetTransmitData(&ack, 1);
                    startMeasurement = 1;
                } break;
                // GET DATA
                case 0x14:{ // master requests measurement data -> send data
                    I2C1_SetTransmitData(measurementData, LENGTH_BYTE);
                    startMeasurement = 1; // start new measurement
                } break;
                default:{
                } break;
            }
        }

        if(startMeasurement){
            doMeasurement();
            startMeasurement = 0;
        }
    }
}
/**
 End of File
*/