#include "buttons.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"


uint8_t measurementData[2];

bool ledState1 = 0;
bool ledState2 = 0;
bool ledState3 = 0;
bool ledState4 = 0;


//--------------------- Interrupt handler switches ------------------
void ISRHandler(void){
// Switch 1 press interrupt
IOCCF2_SetInterruptHandler(LSW1_Toggle);

// Switch 2 press interrupt
IOCCF0_SetInterruptHandler(LSW2_Toggle);

// Switch 3 press interrupt
IOCCF4_SetInterruptHandler(LSW3_Toggle);

// Switch 4 press interrupt
IOCCF6_SetInterruptHandler(LSW4_Toggle);
}

//------------------------------------ Prepare data for transmission ---------------------------------------

void doMeasurement(uint8_t metric, uint8_t * data, uint8_t * length){
    *length = 1;
    data = measurementData;
    measurementData[0] = (!LATCbits.LATC7 << 3) | (!LATCbits.LATC3 << 2) | (!LATCbits.LATC5 << 1) | !LATAbits.LATA2;
    generateInt();
    SLEEP();
}

//---------------------- Generate Interrupt to inform the motherboard that data is ready for transmission -----------------------------
void generateInt(){                         
    READY_SetLow();
    __delay_ms(1);                         
    READY_SetHigh();
}

//---------------------- ISR switches ----------------------
void LSW1_Toggle(void){
    if(ledState1){
        LSW_1_SetHigh(); // LED OFF
    }
    else{
        LSW_1_SetLow(); // LED ON
    }
    ledState1 = (bool)!ledState1;
}

void LSW2_Toggle(void){
    if(ledState2){
        LSW_2_SetHigh(); // LED OFF
    }
    else{
        LSW_2_SetLow(); // LED ON
    }
    ledState2 = (bool)!ledState2;
}

void LSW3_Toggle(void){
    if(ledState3){
        LSW_3_SetHigh(); // LED OFF
    }
    else{
        LSW_3_SetLow(); // LED ON
    }
    ledState3 = (bool)!ledState3;
}

void LSW4_Toggle(void){
    if(ledState4){
        LSW_4_SetHigh(); // LED OFF
    }
    else{
        LSW_4_SetLow(); // LED ON
    }
    ledState4 = (bool)!ledState4;
}

void setThreshold(uint8_t metric, uint8_t * thresholds){
    
}