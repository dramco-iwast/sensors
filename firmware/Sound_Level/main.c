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
 *      Version: 0.2
 *
 *  Description: Generic I2C sensor interface for 
 *                  "IoT with a SOFT touch"
 *               (DRAMCO / KU Leuven TCG project)
 * 
 * -------------------------------------------
 * | Current measurments:                      |
 * -------------------------------------------
 * |     SOUND MODULE ONLY:                    |
 * |             Sleep: +-4.5�A               |
 * |             In WoS: +-25�A               |
 * -------------------------------------------
 * |     SOUND MODULE + MOTHERBOARD:           |
 * |             Sleep: +-30�A                |
 * |             In WoS: +-50�A               |
 * -------------------------------------------
 * 
 * 
 *  - Added external pullup to minimize sleep currents for DOUT pin (pullup)
 * 
 *  Pinout:        ------------------------
 *      TOP:      |  INT  |   GND  |   3V3 |
 *      BOTTOM:   |  SDA  |   SCL  |   NC  |
 *                 ------------------------
 * 
 */

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "global.h"
#include "system/system.h"
#include "system/pin_manager.h"

// include sensor
#include "Sensors/sound_level.h"


Device_API_t sensorAPI = SOUND_API;

uint8_t mData[2 * M_NR];
uint8_t mDataLength;

void toggleInt(void);

/* Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize(SLAVE_ADDRESS);
    
    sensorAPI.Init();
    
    while(1){
        sensorAPI.Loop();
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
                    sensorAPI.Measure();
                } break;
                
                // GET DATA
                case CMD_GET_M_DATA:{ // master requests measurement data -> send data
                    // wait until data are sent
                    uint8_t retries = 20;
                    while(!I2C1_TxBufferEmpty() && retries--){
                        __delay_ms(1);
                    }
                } break;
                
                // INT TOGGLE
                case CMD_INT_TOGGLE:{ //toggle the INT line      
                    toggleInt();
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

void toggleInt(void){
    READY_Toggle();
}

/**
 End of File
*/
