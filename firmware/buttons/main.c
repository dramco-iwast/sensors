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
 *      Created: 2020-10-02
 *       Author: Geoffrey Ottoy
 *      Version: 2.0
 *
 *  Description: Main program implementing common interface for buttons sensor 
 *               in the "IoT with a SOFT touch" project.
 *               (DRAMCO / KU Leuven TCG project)
 * 
 *  Current measurments:
 *      - approx. 330 nA in sleep
 *      - approx. 7 mA for 2 seconds on button press 
 *
 */

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "global.h"
#include "system/system.h"
#include "system/i2c1.h"

// include sensor
#include "sensor/buttons.h"

Sensor_API_t sensorAPI = BUTTONS_API;

uint8_t mData[2 * M_NR];
uint8_t mDataLength;

// keep track of error conditions
uint8_t nr_errors = 0;

/* Main application
 */
void main(void)
{
    // initialize the microcontroller + I2C slave interface
    SYSTEM_Initialize(SLAVE_ADDRESS);
    
    // initialize the sensor
    sensorAPI.Init();
    
    // set the sensor interrupt service routine
    SYSTEM_SetSensorISR(sensorAPI.ISR);
    
    // start main operation
    while(1){
        sensorAPI.Loop();
        // check this!
        sensorAPI.GetData(mData, &mDataLength);
        I2C1_SetTransmitData(mData, mDataLength);
              
        // I2C Slave operation (respond to commands)
        if(I2C1_CommandReceived()){
            uint8_t cmd;
            I2C1_GetCommand(&cmd);
            
            switch(cmd){
                // POLL
                case CMD_POLL:{
                    // master polls address -> respond with ack
                    uint8_t ack = DEFAULT_ACK;
                    I2C1_SetTransmitData(&ack, 1);
                } break;
                
                // TYPE
                case CMD_DEVICE_TYPE:{
                    // master requests sensor type -> respond with type
                    uint8_t type = TYPE_BYTE;
                    I2C1_SetTransmitData(&type, 1);
                } break;

                // NR OF METRICS
                case CMD_GET_M_NR:{
                    // master requests measurement data length -> respond with length
                    uint8_t mnr = M_NR;
                    I2C1_SetTransmitData(&mnr, 1);
                } break;

                // MEASURE
                case CMD_START_MEASUREMENT:{
                    // master forces measurement -> respond with ack
                    //uint8_t ack = DEFAULT_ACK;
                    //I2C1_SetTransmitData(&ack, 1);
                    sensorAPI.Measure();
                } break;
                
                // GET DATA
                case CMD_GET_M_DATA:{ // master requests measurement data -> send data
                    // wait until data are sent
                    uint8_t retries = 20;
                    while(!I2C1_TxBufferEmpty() && retries--){
                        __delay_ms(1);
                    }
                    if(retries == 0){
                        I2C1_ClearTxBuffer();
                        nr_errors++;
                    }
                } break;
                
                // INT TOGGLE
                case CMD_INT_TOGGLE:{ //toggle the INT line      
                    sensorAPI.Ready(TOGGLE);
                } break;
                
                // INT TOGGLE
                case CMD_SET_THRESHOLDS:{ //read thresholds
                    __delay_ms(2);
                    uint8_t len;
                    uint8_t data[20];
                    I2C1_GetCommandData(data, &len);
                    if(len == 6){
                        sensorAPI.UpdateThreshold(data[0], data+1);
                    }
                } break;
                
                // DO NOTHING
                default:{
                } break;
            }
        }
    }
}

/**
 End of File
*/
