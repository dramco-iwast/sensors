#include "buttons.h"
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/pin_manager.h"

#ifdef SENSOR_TYPE
#if (SENSOR_TYPE == BUTTONS)
#warning "Compiling for buttons"

/* local constants ************************************************************/

//

void generateInt(void);

/* function prototypes ********************************************************/

void Buttons_ProcessButtonPress(void);
void LSW1_Pressed(void);
void LSW2_Pressed(void);
void LSW3_Pressed(void);
void LSW4_Pressed(void);

/* local variables ************************************************************/

// variables that control the sampling
__persistent uint8_t buttonsMeasurementData[3 * M_NR];

bool swState1 = false;
bool swState2 = false;
bool swState3 = false;
bool swState4 = false;

/* functions ******************************************************************/
// Interrupt handler switches 
void Buttons_Init(void){
    buttonsMeasurementData[0] = 0x01;
    buttonsMeasurementData[1] = 0x00;
    buttonsMeasurementData[2] = 0x00;
    
    Led0_SetDigitalOutput();
    Led0_SetHigh(); // LED OFF
    
    LSW_1_SetDigitalOutput();
    LSW_2_SetDigitalOutput();
    LSW_3_SetDigitalOutput();
    LSW_4_SetDigitalOutput();
    LSW_1_SetHigh(); // LED OFF
    LSW_2_SetHigh(); // LED OFF
    LSW_3_SetHigh(); // LED OFF
    LSW_4_SetHigh(); // LED OFF
    
    SW_1_SetDigitalInput();
    SW_2_SetDigitalInput();
    SW_3_SetDigitalInput();
    SW_4_SetDigitalInput();
    
    /**
    IOCx registers 
    */
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

    // Switch 1 press interrupt
    IOCCF2_SetInterruptHandler(LSW1_Pressed);

    // Switch 2 press interrupt
    IOCCF0_SetInterruptHandler(LSW2_Pressed);

    // Switch 3 press interrupt
    IOCCF4_SetInterruptHandler(LSW3_Pressed);

    // Switch 4 press interrupt
    IOCCF6_SetInterruptHandler(LSW4_Pressed);
    
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
}

// don't use this function -> buttons work inherently "threshold-based"
void Buttons_ReadButtons(void){
    //buttonsMeasurementData = (!LATCbits.LATC7 << 3) | (!LATCbits.LATC3 << 2) | (!LATCbits.LATC5 << 1) | !LATAbits.LATA2;
    generateInt();
}

void Buttons_ProcessButtonPress(void){
    // Disable interrupts
    PIE0bits.IOCIE = 0; 
    
    //buttonsMeasurementData= 0x00;
    if(swState1){
       buttonsMeasurementData[2] |= 0x01;
    }
    if(swState2){
       buttonsMeasurementData[2] |= 0x02;
    }
    if(swState3){
       buttonsMeasurementData[2] |= 0x04;
    }
    if(swState4){
       buttonsMeasurementData[2] |= 0x08;
    }
    if(buttonsMeasurementData[2]){
        generateInt();
    }
}

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
    }
    // Enable interrupts
    IOCCF = 0x00; // clear all interrupts that might have occurred during animation
    PIE0bits.IOCIE = 1;  
    
    SLEEP();
    NOP();
}

void Buttons_GetData(uint8_t * data, uint8_t  * length){
    *length = M_NR*3;
    data[0] = buttonsMeasurementData[0];
    data[1] = buttonsMeasurementData[1];
    data[2] = buttonsMeasurementData[2];
    buttonsMeasurementData[2] = 0x00;
}

void Buttons_SetThreshold(uint8_t metric, uint8_t * thresholds){
    return;
}

//---------------------- ISR switches ----------------------
void LSW1_Pressed(void){
    swState1 = true;
    Buttons_ProcessButtonPress();
}

void LSW2_Pressed(void){
    swState2 = true;
    Buttons_ProcessButtonPress();
}

void LSW3_Pressed(void){
    swState3 = true;
    Buttons_ProcessButtonPress();
}

void LSW4_Pressed(void){
    swState4 = true;
    Buttons_ProcessButtonPress();
}

// Toggle the interrupt line
void generateInt(void){
    READY_SetLow();
    __delay_ms(1);                          
    READY_SetHigh();
}

#endif
#endif
