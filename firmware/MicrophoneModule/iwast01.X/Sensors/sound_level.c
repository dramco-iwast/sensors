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
 *      Version: 0.2
 *
 *  Description: Sound Level Sensor
 *
 */

#include "sound_level.h"
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/adcc.h"

/* local constants ************************************************************/

#define SAMPLES 400 // amount of samples

/* function prototypes ********************************************************/

// prepare data for transmission
void prepTransmission(void);

// start the ADC (continuous sampling)
void startADC(void);

// stop ADC operation
void stopADC(void);

// callback for adc interrupt
void getSample(void);

// generate low pulse on interrupt line
void generateInt(void);

// enable microphone
void enableMic(void);

// disable microphone
void disableMic(void);

// debug led on
void ledOn(void);

// debug led off
void ledOff(void);

// debug led toggle
void ledToggle(void);

/* local variables ************************************************************/

// variables that control the sampling
bool measurementRunning = false;
uint16_t sampleCounter = 0;         
__persistent uint16_t maxValue = 0;
bool autoStart = false;

// buffer that holds the maxValue ( msb | lsb)
__persistent uint8_t measurementData[2];

// variables for threshold-based operation
// TODO: disable again
__persistent uint8_t thresholdEnabled = 0;
__persistent uint16_t thresholdLevel = 0;

/* functions ******************************************************************/

// initialize peripherals needed for sensor operation
void init(void){
    // enable led output
    TRISB &= 0xBF; // RB6 = output
    
    // initialize ADC
    ADCC_Initialize();
    ADCC_SetADIInterruptHandler(getSample);
    
    // initialize timer for periodic measurements
    // setup watchdog
    WDTCON0 = 0x14; // 1 second period
    WDTCON1 = 0x07; // LFINTOSC, window 100%
    
    // wwdt reset (while awake)
    if(STATUSbits.nTO == 0){
        WDTCON0bits.SWDTEN = 1; //start watchdog -> results in reset after 1 s
        autoStart = true;
        measure();
    }
    else{
        thresholdEnabled = 0;
        WDTCON0bits.SWDTEN = 0;
    }
}

void measure(){
    CLRWDT();
    ledOn();
    
    measurementRunning = true;
    sampleCounter = 0;
    maxValue = 0;
    
    enableMic();
    __delay_ms(50); // wait 50 ms to startup the mic
    startADC();     // adc conversion will result in ADC ISR -> getSample
    
    // wait until measurement is complete
    while(measurementRunning);
    
    stopADC();
    disableMic();
    
    prepTransmission();
}

/* does sensor loop stuff
 */
void loop(void){
    /* go to sleep
     * possible wake-up sources in this case:
     *  - i2c clock line goes active
     *  - watchdog timer overflow
     */
    SLEEP();
    NOP();

    // watchdog timer overflow has occurred while sleeping
    if(STATUSbits.nTO == 0){
        WDTCON0bits.SWDTEN = 1; //start watchdog -> results in reset after 1 s
        autoStart = true;
        measure();
    }
}

/* copy data 
 */
void getData(uint8_t * data, uint8_t * length){
    // this is fixed
    *length = 2;
    data[0] = measurementData[0];
    data[1] = measurementData[1]; 
}

void setThreshold(uint8_t metric, uint8_t * thresholdData){
    if(metric == 0){
        thresholdEnabled = thresholdData[0];
        thresholdLevel = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        
        if(thresholdEnabled){
            WDTCON0bits.SWDTEN = 1;
        }
    }
}

//------------------------------------ Prepare data for transmission ---------------------------------------
void prepTransmission(){
    measurementData[0] = maxValue>>8;
    measurementData[1] = maxValue;
    
    if(autoStart){
        autoStart = false;
        // only generate interrupt when maxiValue exceeds thresholdLevel
        if(maxValue > thresholdLevel){
            generateInt();
        }
    }
    else{
        // generate interrupt because measurement has started on motherboard's request
        generateInt();
    }
    
    ledOff();
}

// This function is called when an ADC-conversion has completed
void getSample(){
    uint16_t sample = ADCC_GetConversionResult();
    
    // Check whether the new value is bigger than the previous maximum value
    if(sample > maxValue){
        maxValue = sample;
    }
    
    sampleCounter++;
    if(sampleCounter>SAMPLES-1){ // we've taken enough samples
        measurementRunning = false;
    }   
}

// Prepare ADC for continuous conversion and start the sampling at 20 kHz
void startADC(){                       
    ADCC_EnableContinuousConversion();
    ADCC_StartConversion(channel_ANC1);
}


// Stop the ADC conversions
void stopADC(){                             
    ADCC_StopConversion();
    ADCC_DisableContinuousConversion();
}


// Generate Interrupt to inform the motherboard that data is available
void generateInt(){                         
    READY_SetLow();
    __delay_ms(1);                         
    READY_SetHigh();
}


// Enable microphone and amplifiers on the microphone module
void enableMic(){
    powerMic_SetHigh();
}


// Disable microphone and amplifiers on the microphone module
void disableMic(){
    powerMic_SetLow();
}

// debug led on
void ledOn(void){
    LATB |= 0x40; // RB6 = 1
}

// debug led off
void ledOff(void){
    LATB &= 0xBF; // RB6 = 0
}

// debug led toggle
void ledToggle(void){
    LATB ^= 0x40;
}
