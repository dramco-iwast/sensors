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
 *  Description: Sound Level Sensor Implementation
 *
 */

#include <math.h>
#include "sound_level.h"
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/adcc.h"

#ifdef SENSOR_TYPE
#if (SENSOR_TYPE == SOUND_LEVEL)
#warning "Compiling for Sound_level sensor"

/* local constants ************************************************************/

#define SAMPLES         400 // amount of samples
#define AMP_FACTOR      44
#define SENSITIVITY     0.01258925
#define V_SUPPLY        3.3
#define ADC_SCALE       4095
#define REF_PRESSURE    20e-6
#define DBZ_MAX         106
#define SCALE_FACTOR    600

/* 'local' function prototypes ************************************************/

// prepare data for transmission
void SoundLevel_PrepareData(void);

// start the ADC (continuous sampling)
void SoundLevel_StartADC(void);

// stop ADC operation
void SoundLevel_StopADC(void);

// callback for ADC interrupt
void SoundLevel_GetSample(void);

// 'active' led on
void SoundLevel_LedOn(void);

// 'active' led off
void SoundLevel_LedOff(void);

// 'active' led toggle
void SoundLevel_LedToggle(void);

void generateInt(void);
void measure(void);

/* local variables ************************************************************/

// variables used during the sampling
float presSumSquared;
float adcScaler;
bool measurementRunning = false;
uint16_t sampleCounter = 0;   

volatile uint8_t measurementData[3];
uint8_t dLen = 0;

// buffer that holds the maxValue ( msb | lsb)
uint8_t thresholdEnabled = 0;
uint16_t thresholdLevel = 0;

bool polledMeasurement = false;
bool overThreshold = false;

/* Sensor API functions *******************************************************/

/* Initialize peripherals needed for sound level detection
 */
void SoundLevel_Init(void){
#ifdef BLINK_ACTIVE_LED
    // enable led output
    TRISB &= 0xBF; // RB6 = output
#endif
       
    nWakeMic_SetDigitalOutput();
    powerMic_SetDigitalOutput();
    
    adcScaler = V_SUPPLY / (ADC_SCALE * SENSITIVITY * AMP_FACTOR);
    
    // initialize ADC
    ADCC_Initialize();
    ADCC_SetADIInterruptHandler(SoundLevel_GetSample);
    
    // initialize timer for periodic measurements
    // setup watchdog (WWDT))
    WDTCON0 = 0x14; // 1 second period
    WDTCON1 = 0x07; // LFINTOSC, window 100%
    
    // WWDT reset (while awake)
    /*if(STATUSbits.nTO == 0){
        WDTCON0bits.SWDTEN = 1; //start watchdog -> results in reset after 1 s
        autoStart = true;
        SoundLevel_Measure();
    }
    else{
        thresholdEnabled = 0;
        WDTCON0bits.SWDTEN = 0;
    }*/
}

/* Measure the sound level (MCU remains active)
 */
void SoundLevel_Measure(){
    polledMeasurement = true;
}

/* does sensor loop stuff
 */
void SoundLevel_Loop(void){
    bool startMeasurement = false;
    // watchdog timer overflow has occurred while sleeping
    if(STATUSbits.nTO == 0){
        WDTCON0bits.SWDTEN = 1; //start watchdog -> results in reset after 1 s
        startMeasurement = true;
    }
    
    if(startMeasurement || polledMeasurement){
        measure();
    }
    else{
        /* go to sleep
         * possible wake-up sources in this case:
         *  - i2c clock line goes active
         *  - watchdog timer overflow
         */
        SLEEP();
        NOP();
    }
}

/* copy data to buffer
 */
void SoundLevel_GetData(uint8_t * data, uint8_t * length){
    *length = 3; // this is fixed (M_NR = 1)
    data[0] = measurementData[0];
    data[1] = measurementData[1]; 
    data[2] = measurementData[2];
    //data = measurementData;
}

/* Sensor 'local' functions ***************************************************/

/* Set sound threshold level (and enable/disable) thresholds
 */
void SoundLevel_SetThreshold(uint8_t metric, uint8_t * thresholdData){
    if(metric == 0){
        thresholdEnabled = thresholdData[0];
        thresholdLevel = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        
        if(thresholdEnabled){
            WDTCON0bits.SWDTEN = 1;
        }
    }
}

/* Prepare data for transmission 
 */
void SoundLevel_PrepareData(){
    float presAvgSquared = presSumSquared/SAMPLES;
    float dBZ = 10 * log10(presAvgSquared/(REF_PRESSURE * REF_PRESSURE));
    
    if(dBZ > DBZ_MAX){
        dBZ = DBZ_MAX;
    }

    uint16_t dataToSend = (uint16_t)(round(dBZ * SCALE_FACTOR));
    //uint16_t dataToSend = 0x1234;
    
    measurementData[0] = 0x01;
    measurementData[1] = (uint8_t)(dataToSend>>8);
    measurementData[2] = (uint8_t)(dataToSend);
    dLen = 3 * M_NR;
    
    // notify motherboard
    if(polledMeasurement){
        polledMeasurement = false;
        generateInt();
    }
    else{
        // only generate interrupt when maxiValue exceeds thresholdLevel
        if(dataToSend > thresholdLevel){
            if(!overThreshold){
                overThreshold = true;
                generateInt();
            }
        }
        overThreshold = false;
        // make sure watchdog is running again
        WDTCON0bits.SWDTEN = 1;
    }

    
    // show not 'active'
    SoundLevel_LedOff();
}

// This function is called when an ADC-conversion has completed
void SoundLevel_GetSample(){
    uint16_t sample = ADCC_GetConversionResult();    
    
    //float voltageToPressure = sample * adcScaler;
    float sampleToVoltage = (3.3*sample)/(4095);                                      //Calculate the equivalent voltage value at output of mic
    float voltageToPressure = sampleToVoltage/(0.01258925 * 44);
    
    presSumSquared = presSumSquared + (voltageToPressure * voltageToPressure);
    //presSumSquared = presSumSquared + (sample*sample)
    
    sampleCounter++;
    if(sampleCounter>SAMPLES-1){ // we've taken enough samples
        measurementRunning = false;
    }   
}

// Prepare ADC for continuous conversion and start the sampling at 20 kHz
void SoundLevel_StartADC(){                       
    ADCC_EnableContinuousConversion();
    ADCC_StartConversion(channel_ANC1);
}

// Stop the ADC conversions
void SoundLevel_StopADC(){                             
    ADCC_StopConversion();
    ADCC_DisableContinuousConversion();
}

// 'active' led on
void SoundLevel_LedOn(void){
#ifdef BLINK_ACTIVE_LED
    LATB |= 0x40; // RB6 = 1
#endif
}

// 'active' led off
void SoundLevel_LedOff(void){
#ifdef BLINK_ACTIVE_LED
    LATB &= 0xBF; // RB6 = 0
#endif
}

// 'active' led toggle
void SoundLevel_LedToggle(void){
#ifdef BLINK_ACTIVE_LED
    LATB ^= 0x40;
#endif
}

// Toggle the interrupt line
void generateInt(void){
    READY_SetLow();
    __delay_ms(1);                          
    READY_SetHigh();
}

void measure(void){
    CLRWDT();               // feed the dog
    SoundLevel_LedOn();     // show 'active'
    
    // initialize control variables
    measurementRunning = true;
    sampleCounter = 0;
    presSumSquared = 0;
    
    // power-on microphone and amplifier circuit
    powerMic_SetHigh();
    nWakeMic_SetLow();
    __delay_ms(100);         // wait until stable
    SoundLevel_StartADC();  // ADC conversion will be handled by 
                            // SoundLevel_GetSample callback
    
    // wait until measurement is complete
    while(measurementRunning);
    
    // stop conversions and power-down analog circuitry
    SoundLevel_StopADC();
    nWakeMic_SetHigh();
    powerMic_SetLow();
    
    
    // prepare measurement for transmission
    SoundLevel_PrepareData();
}

#endif
#endif
