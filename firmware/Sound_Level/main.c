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
 *  Current measurments:
 *      - approx. 370µA sleep
 *      - approx. 288µA sleep between measurements of 1 minute, 954.51µW (50sec)
 *      - approx. 34.64µA sleep without MIC on, 114.97µW (50sec)
 * 
 *      - approx. 69µA extra by disabling VREGCONbits.VREGPM = 1;
 * 
 *      - approx. 25.7µA threshold based -> improved to 19µA (incorrect LED initialisation)
 *                                       -> improved to 10.4µA (PIN_MANAGER_Initialize() bad initialisation)
 * -------------------------------------------
 *      - approx. 1.37µA in SLEEP
 *      - approx. 260µA MIC ON      
 * -------------------------------------------
 * 
 *      - 868.68µA -> MIC voltage duty cycle
 *      - 449.36µA -> MIC always ON without delay
 *      - 1.09mA -> MIC always ON + 100ms delay
 *      --> Best option:
 *          - Threshold mode: MIC always ON
 *          - Polling mode: MIC voltage duty cycle
 * 
 * 
 *  Pinout:        ------------------------
 *      TOP:      |  INT  |   GND  |   3V3 |
 *      BOTTOM:   |  SDA  |   SCL  |   NC  |
 *                 ------------------------
 * 
 */

#include "mcc_generated_files/mcc.h"
#include "global.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mcc_generated_files/pin_manager.h"

// include sensor
#include "Sensors/sound_level.h"

#include <xc.h>

Device_API_t sensorAPI = SOUND_API;


uint8_t mData[2 * M_NR];
//uint8_t * mData;
uint8_t mDataLength;

void toggleInt(void);

/* Main application
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

    //READY_SetHigh();
    
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
