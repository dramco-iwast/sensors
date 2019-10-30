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
 *         File: sound_level.c
 *      Created: 2019-09-11
 *       Author: Matthias Alleman
 *      Version: 0.1
 *
 *  Description: Sound Level Sensor
 *
 */


#include "sound_level.h"
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/adcc.h"


#define SAMPLES 400 // amount of samples

bool reset = false;                                             // when true, the value of "value"
uint16_t x = 0;         
uint16_t maxValue = 0;

uint8_t measurementData[2];

void dummy(void){
    return;
}

//------------------------------------ initialize the ADC ---------------------------------------
void doMeasurement(uint8_t metric, uint8_t * data, uint8_t * length){
    // this is fixed
    *length = 2;
    data = measurementData;
    enableMic();
    initializeADC();  
}

//------------------------------------ Prepare data for transmission ---------------------------------------
void prepTransmission(uint16_t maxiValue){
    stopADC();
    disableMic();
    measurementData[0] = maxiValue>>8;
    measurementData[1] = maxiValue;
    generateInt();
    SLEEP();
}

//--------------------------------------This function is called when an ADC-conversion has completed  -----------------------------------------------------------
void getValue(){

    uint16_t sample = ADCC_GetConversionResult();    // Put the 12-bit value in the variable "sample"
        
        
        if(sample > maxValue){              // Check whether the new value is bigger or smaller than the maximum value that already has been sampled
            maxValue = sample;
        }
    
        if(x >= SAMPLES-1){                 // Check whether the ADC has finished
            reset = true;              // The resetboolean is set to true make sure all the variables are reset to 0
            prepTransmission(maxValue);
        }
    x++;                                    // Increment x
    
    if(reset){                         // reset the variables
            reset = false;                
            maxValue = 0;
            sample = 0;   
            x=0;
        }
            

}

//------------------------prepare ADC for continuous conversion and start the sampling at 20 kHz
void initializeADC(){                       
    __delay_ms(50);                         // wait 50 ms to startup the mic
    ADCC_Initialize();
    ADCC_EnableContinuousConversion();
    ADCC_StartConversion(channel_ANC1);
}


//-----------------------Stop the ADC conversions-------------------------------------
void stopADC(){                             
    ADCC_StopConversion();
    ADCC_DisableContinuousConversion();
}


//----------------------Generate Interrupt to inform the motherboard that data is ready for transmission -----------------------------
void generateInt(){                         
    READY_SetLow();
    __delay_ms(1);                         
    READY_SetHigh();
}


//----------------------Enable microphone and amplifiers on the microphone module -----------------------------
void enableMic(){
    powerMic_SetHigh();
}


//----------------------Disable microphone and amplifiers on the microphone module -----------------------------
void disableMic(){
    powerMic_SetLow();
}






void setThreshold(uint8_t metric, uint8_t * thresholds){
    
}