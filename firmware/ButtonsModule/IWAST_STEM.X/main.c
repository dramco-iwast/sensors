/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18446
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "global.h"

#include <stdio.h>
#include <string.h>

// include sensor
#include "buttons.h"

Device_API_t sensorAPI = SENSOR_API;

#ifndef TYPE_BYTE
    #error "TYPE_BYTE is not defined"
#elif (~(~TYPE_BYTE + 0) == 0 && ~(~TYPE_BYTE + 1) == 1)
    #error "TYPE_BYTE is defined, but has no value"
#endif

#ifndef M_NR
    #error "LENGTH_BYTE is not defined"
#elif (~(~LENGTH_BYTE + 0) == 0 && ~(~LENGTH_BYTE + 1) == 1)
    #error "LENGTH_BYTE is defined, but has no value"
#endif


#ifndef SLAVE_ADDRESS
    #error "SLAVE_ADDRESS is not defined"
#elif (~(~SLAVE_ADDRESS + 0) == 0 && ~(~SLAVE_ADDRESS + 1) == 1)
    #error "SLAVE_ADDRESS is defined, but has no value"
#endif


void toggleInt(void);
//extern uint8_t measurementData[];

//bool startMeasurement = 0;

uint8_t measurementData[2 * M_NR];
uint8_t mDataLength;


/*
                         Main application
 */

void main(void){
    
    // initialize the device
    SYSTEM_Initialize(SLAVE_ADDRESS);
        
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    sensorAPI.Init();
  
    while (1)
    {
        
        // I2C Slave operation (respond to commands)
        if(I2C1_CommandReceived()){
            uint8_t cmd;
            uint8_t len;
            uint8_t data[20];
            I2C1_GetCommand(&cmd, data, &len);
            
            switch(cmd){
                // POLL
                case CMD_POLL:{ // master polls address -> respond with ack
                    uint8_t ack = DEFAULT_ACK;
                    I2C1_SetTransmitData(&ack, 1);
                    SLEEP();

                } break;
                
                // TYPE
                case CMD_DEVICE_TYPE:{ // master requests sensor type -> respond with type
                    uint8_t type = TYPE_BYTE;
                    I2C1_SetTransmitData(&type, 1);
                    SLEEP();
                } break;
                
                // NR OF METRICS
                case CMD_GET_M_NR:{ // master requests measurement data length -> respond with length
                    uint8_t mnr = M_NR;
                    I2C1_SetTransmitData(&mnr, 1);
                    SLEEP();
                } break;
                
                // MEASURE
                case CMD_START_MEASUREMENT:{ // master forces measurement -> respond with ack
                    uint8_t metric = data[0];
                    uint8_t ack = DEFAULT_ACK;
                    I2C1_SetTransmitData(&ack, 1);
                    sensorAPI.Measure(metric, measurementData, &mDataLength);
                } break;
                
                // GET DATA
                case CMD_GET_M_DATA:{ // master requests measurement data -> send data
                    I2C1_SetTransmitData(measurementData, mDataLength);
                    //for (int i=0; i<600; i++){}
                    SLEEP();     
                } break;
                
                // INT TOGGLE
                case CMD_INT_TOGGLE:{ //toggle the INT line      
                    uint8_t ack = 0xAA;
                    I2C1_SetTransmitData(&ack, 1); 
                    toggleInt();
                    SLEEP();
                } break;
                
                // DO NOTHING
                default:{
                } break;
            }
        }

           
        /*
        Led0_SetHigh();
        __delay_ms(1000);
        Led0_SetLow();
        __delay_ms(1000);
         */
    }
}

//----------------Toggle the interrupt line ------------------
void toggleInt(){
    READY_SetLow();
    __delay_ms(1);
    READY_SetHigh();
}

/**
 End of File
*/