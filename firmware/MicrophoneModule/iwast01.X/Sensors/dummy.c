#include "Dummy.h"
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/adcc.h"




//------------------------------------ initialize the ADC ---------------------------------------
void doMeasurement(void){
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
    
        if(x >= samples-1){                 // Check whether the ADC has finished
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


//----------------------Toggle the interrupt line -----------------------------
void toggleInt(){
    READY_SetLow();
    __delay_ms(1);                          
    READY_SetHigh();
}


