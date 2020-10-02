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
 *         File: buttons.c
 *      Created: 2020-10-02
 *       Author: Geoffrey Ottoy
 *      Version: 2.0
 *
 *  Description: Implements the "buttons sensor" behavior for the 
 *               "IoT with a SOFT touch" project, following the Sensor_API_t
 *               description.
 * 
 */

#include "buttons.h"

/* local constants ************************************************************/

/* static functions ***********************************************************/
// Generate "low" pulse on ready pin
static void Buttons_GenerateInterrupt(void){
    READY_SetLow();
    __delay_ms(1);                          
    READY_SetHigh(); // default state
}

/* local variables ************************************************************/

// variables that control the sampling
uint8_t buttonsMeasurementData[2 * M_NR];

bool swState1 = false;
bool swState2 = false;
bool swState3 = false;
bool swState4 = false;

bool dataSent = false;

/* functions for SENSOR_API ***************************************************/

// Device_API_t -> ISR
// Handle pin interrupts
void Buttons_ISR(void){
    if(PIE0bits.IOCIE == 1 && PIR0bits.IOCIF == 1){
        if(dataSent){
            buttonsMeasurementData[1] = 0x00;
        }
        // interrupt on change for pin IOCCF2 (RC2 = SW1)
        if(IOCCFbits.IOCCF2 == 1){
            IOCCFbits.IOCCF2 = 0;
            swState1 = true;
            buttonsMeasurementData[1] |= 0x01;
        }
        // interrupt on change for pin IOCCF0 (RC0 = SW2)
        if(IOCCFbits.IOCCF0 == 1){
            IOCCFbits.IOCCF0 = 0;
            swState2 = true;
            buttonsMeasurementData[1] |= 0x2;
        }	
        // interrupt on change for pin IOCCF4 (RC4 = SW3)
        if(IOCCFbits.IOCCF4 == 1){
            IOCCFbits.IOCCF4 = 0;
            swState3 = true;
            buttonsMeasurementData[1] |= 0x04;
        }	
        // interrupt on change for pin IOCCF6 (RC6 = SW4)
        if(IOCCFbits.IOCCF6 == 1){
            IOCCFbits.IOCCF6 = 0;
            swState4 = true;
            buttonsMeasurementData[1] |= 0x08;
        }
        PIR0bits.IOCIF = 0;
    }
}

// Device_API_t -> Init
// Initialize pins, LEDs and interrupts
void Buttons_Init(void){
    // configure READY pin
    READY_SetDigitalOutput();
    READY_SetHigh();
    
    buttonsMeasurementData[0] = 0x00;
    buttonsMeasurementData[1] = 0x00;
    
    // configure LED pin (only used for debugging)
    Led0_SetDigitalOutput();
    Led0_SetHigh(); // LED OFF
    
    // configure pins that control the LEDs inside the switches
    LSW_1_SetDigitalMode();
    LSW_2_SetDigitalMode();
    LSW_3_SetDigitalMode();
    LSW_4_SetDigitalMode();
    LSW_1_SetDigitalOutput();
    LSW_2_SetDigitalOutput();
    LSW_3_SetDigitalOutput();
    LSW_4_SetDigitalOutput();
    LSW_1_SetHigh(); // LED OFF
    LSW_2_SetHigh(); // LED OFF
    LSW_3_SetHigh(); // LED OFF
    LSW_4_SetHigh(); // LED OFF
    
    // configure pins connected to the switches
    SW_1_SetDigitalMode();
    SW_2_SetDigitalMode();
    SW_3_SetDigitalMode();
    SW_4_SetDigitalMode();
    SW_1_SetDigitalInput();
    SW_2_SetDigitalInput();
    SW_3_SetDigitalInput();
    SW_4_SetDigitalInput();
    
    // configure interrupt on change registers
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF0 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF2 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF4 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF6 = 0;
    
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN0 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN2 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN4 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN6 = 1;
    
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP0 = 0;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP2 = 0;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP4 = 0;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP6 = 0;
    
    // Enable IOC interrupt 
    PIE0bits.IOCIE = 1; 
    
}

// Device_API_t -> Measure
// don't use this function -> buttons work inherently "threshold-based"
void Buttons_ReadButtons(void){
    return;
}

// Device_API_t -> Loop
// Loop behavior for buttons, i.e., basically a "LED show" when one of the
// switches is pressed.
void Buttons_Loop(void){
    // Button press "animation" on button leds
    if(swState1 | swState2 | swState3 | swState4){        
        LSW_1_SetLow(); // LED ON
        LSW_2_SetLow(); // LED ON
        LSW_3_SetLow(); // LED ON
        LSW_4_SetLow(); // LED ON
        
        __delay_ms(500);
        
        LSW_1_SetHigh(); // LED OFF
        LSW_2_SetHigh(); // LED OFF
        LSW_3_SetHigh(); // LED OFF
        LSW_4_SetHigh(); // LED OFF
        
        
        for(uint8_t i=0; i<255; i++){
            uint8_t onTime = 255-i;
            uint8_t offTime = i;
            if(swState1){
                LSW_1_SetLow(); // LED ON
            }
            if(swState2){
                LSW_2_SetLow(); // LED ON
            }
            if(swState3){
                LSW_3_SetLow(); // LED ON
            }
            if(swState4){
                LSW_4_SetLow(); // LED ON
            }
            for(uint8_t j=0; j<onTime; j++){
                __delay_us(20);
            }
            LSW_1_SetHigh(); // LED OFF
            LSW_2_SetHigh(); // LED OFF
            LSW_3_SetHigh(); // LED OFF
            LSW_4_SetHigh(); // LED OFF
            for(uint8_t j=0; j<offTime; j++){
                __delay_us(20);
            }
        }
        
        swState1 = false;
        swState2 = false;
        swState3 = false;
        swState4 = false;
        dataSent = false;
        
        Buttons_GenerateInterrupt();
    }
    // Enable interrupts
    IOCCF = 0x00; // clear all interrupts that might have occurred during animation
    PIE0bits.IOCIE = 1;  
    
    SLEEP();
    NOP();
}

// Device_API_t -> GetData
// Copy local measurement, i.e., the buttons that have been pressed to 'data'
void Buttons_GetData(uint8_t * data, uint8_t  * length){
    *length = 2;
    data[0] = buttonsMeasurementData[0];
    data[1] = buttonsMeasurementData[1];
    dataSent = true;
}

// Device_API_t -> SetThreshold
// Required by SENSOR_API, but does nothing.
void Buttons_SetThreshold(uint8_t metric, uint8_t * thresholds){
    return;
}

// Device_API_t -> Ready
// Control the ready pin
void Buttons_Ready(ReadyMode_t mode){
    switch(mode){
        case SET: READY_SetHigh();
        break;
        case CLEAR: READY_SetLow();
        break;
        default: READY_Toggle();
        break;
    }
}