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
 *       Author: Matthias Alleman - Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Sound Level Sensor Implementation
 *
 */

#include <math.h>
#include "sound_level.h"
#include "../system/system.h"
#include "../system/adcc.h"

#ifdef SENSOR_TYPE
#if (SENSOR_TYPE == SOUND_LEVEL)
#warning "Compiling for Sound_level sensor"

/* local constants ************************************************************/

#define SAMPLES         400 // amount of samples
#define AMP_FACTOR      44
#define SENSITIVITY     0.01258925
#define V_SUPPLY        3.3 //3.1 // measured voltage when sampling
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

// generate Interrupt to main board
void generateInt(void);

// measure sound
void measure(void);

// Sleep functionality
static void EnterSleep(void);

// init leds
void LED_Init(void);

// deinit leds
void LED_DeInit(void);

// blink functionality
void LED_Blink(void);

// Initialize power to the MIC and wakeup circuits
void powerMic_Init(void);

// Initialize nWakeMic
void nWakeMic_Init(void);

// Initialize READY interrupt pin to warn central microcontroller
void READY_Init(void);

// Initialize watchdog timer
void WDT_Init(void);

/* local variables ************************************************************/

// variables used during the sampling
float presSumSquared;
float adcScaler;
bool measurementRunning;
bool sampling = false;
uint16_t sampleCounter = 0;   

volatile uint8_t measurementData[2];
uint8_t dLen = 0;

// buffer that holds the maxValue ( msb | lsb)
__persistent uint8_t thresholdEnabled;
__persistent uint16_t thresholdLevel;

bool polledMeasurement = false;
bool overThreshold = false;

/* Sensor API functions *******************************************************/

/* Initialize LED */
void LED_Init(void)
{
    #ifdef BLINK_ACTIVE_LED
    LED_SetDigitalMode();
    LED_SetDigitalOutput();
    SoundLevel_LedOff();
    LED_Blink();
    #endif
}

/* DeInitialize LED */
void LED_DeInit(void)
{
    #ifdef BLINK_ACTIVE_LED
    TRISBbits.TRISB6 = 1; // disable led output
    #endif
}

/* Animation when Sound Module is plugged in */
void LED_Blink(void)
{
    SoundLevel_LedOn();
    __delay_ms(100);
    SoundLevel_LedOff();
    __delay_ms(100);
    SoundLevel_LedOn();
    __delay_ms(100);
    SoundLevel_LedOff();
    __delay_ms(500);
    SoundLevel_LedOn();
    __delay_ms(100);
    SoundLevel_LedOff();
    __delay_ms(100);
    SoundLevel_LedOn();
    __delay_ms(100);
    SoundLevel_LedOff();
}

void powerMic_Init(void)
{
    powerMic_SetDigitalMode();
    powerMic_SetDigitalOutput();
    powerMic_SetHigh();
    __delay_ms(100);
    powerMic_SetLow(); // prevents it from powering the MIC the in the time before the first measurement when sensor is in polled mode
}

void nWakeMic_Init(void)
{
    nWakeMic_SetDigitalMode();
    nWakeMic_SetDigitalOutput();
    nWakeMic_SetLow();
    __delay_ms(100);
}

void READY_Init(void)
{
    READY_SetDigitalOutput();
    READY_SetHigh();
}

void WDT_Init(void)
{
    // initialize timer for periodic measurements   
    WDTCON0 = 0x14; // 1 second period
    WDTCON1 = 0x07; // LFINTOSC, window 100%
}

/* Initialize peripherals needed for Sound Level detection */
void SoundLevel_Init(void){

    LED_Init(); // Initialize LED
    
    PMD0bits.IOCMD = 0; // Enable gpio clock
    
    nWakeMic_Init();
    powerMic_Init();
    READY_Init();

    adcScaler = V_SUPPLY / (ADC_SCALE * SENSITIVITY * AMP_FACTOR);
    
    // initialize ADC
    ADCC_Initialize();
    ADCC_SetADIInterruptHandler(SoundLevel_GetSample);
    
    // setup watchdog (WWDT))
    WDT_Init();
    
    thresholdEnabled = false;

    // start watchdog
    CLRWDT();
    WDTCON0bits.SWDTEN = 1;
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
        if(!measurementRunning && thresholdEnabled) startMeasurement = true;
    }
    if(thresholdEnabled == false) powerMic_SetLow();// fix for problem of MICs staying powered when switching from threshold mode to polling mode during first sleep period

    CLRWDT();
    if(startMeasurement || polledMeasurement){
        measurementRunning = true;
        measure();
        polledMeasurement = false;
        measurementRunning = false;
        CLRWDT();
    }
    else{
        /* go to sleep
         * possible wake-up sources in this case:
         *  - i2c clock line goes active
         *  - watchdog timer overflow
         */
        EnterSleep();
    }
}

static void EnterSleep(void){
    CPUDOZEbits.IDLEN = 0; // make sure PIC is not in doze mode before going to sleep   
    NOP();
    SLEEP(); // enter sleep
    NOP();
    NOP();
}

/* copy data to buffer */
void SoundLevel_GetData(uint8_t * data, uint8_t * length){
    *length = 2; // this is fixed (M_NR = 1)
    data[0] = measurementData[0];
    data[1] = measurementData[1];
}

/* Set sound threshold level (and enable/disable) thresholds */
void SoundLevel_SetThreshold(uint8_t metric, uint8_t * thresholdData){
    if(metric == 0){
        thresholdEnabled = thresholdData[0];
        thresholdLevel = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        
        if(thresholdEnabled){
            WDTCON0bits.SWDTEN = 1;
        }
    }
}

/* Prepare data for transmission */
void SoundLevel_PrepareData(){
    float presAvgSquared = presSumSquared/SAMPLES;
    float dBZ = 10 * log10(presAvgSquared/(REF_PRESSURE * REF_PRESSURE));
    
    if(dBZ > DBZ_MAX){
        dBZ = DBZ_MAX;
    }

    uint16_t dataToSend = (uint16_t)(round(dBZ * SCALE_FACTOR));

    measurementData[0] = (uint8_t)(dataToSend>>8);
    measurementData[1] = (uint8_t)(dataToSend);
    
    // notify motherboard
    if(polledMeasurement){
        generateInt();
    }
    else{
        // only generate interrupt when maxiValue exceeds thresholdLevel
        if(dataToSend > thresholdLevel){
            if(!overThreshold){
                overThreshold = true;
                generateInt();
                SoundLevel_LedOn(); // only blink LED if value is above threshold
                __delay_ms(100);
                SoundLevel_LedOff();
            }
        }
        else{
            overThreshold = false;
        }
        // make sure watchdog is running again
        WDTCON0bits.SWDTEN = 1;
    }

    // show not 'active'
    if(polledMeasurement == true) // only blink LED if it's a polled measurement
    {
        SoundLevel_LedOff();
    }
}

// This function is called when an ADC-conversion has completed
void SoundLevel_GetSample(){
    uint16_t sample = ADCC_GetConversionResult();    
    
    float voltageToPressure = sample * adcScaler;
    
    presSumSquared = presSumSquared + (voltageToPressure * voltageToPressure);
    
    sampleCounter++;
    if(sampleCounter>SAMPLES-1){ // we've taken enough samples
        sampling = false;
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
    LED_SetHigh();
#endif
}

// 'active' led off
void SoundLevel_LedOff(void){
#ifdef BLINK_ACTIVE_LED
    LED_SetLow();
#endif
}

// 'active' led toggle
void SoundLevel_LedToggle(void){
#ifdef BLINK_ACTIVE_LED
    LED_Toggle();
#endif
}

// Toggle the interrupt line
void generateInt(void){
    READY_SetLow();
    __delay_ms(5);                          
    READY_SetHigh();
}

void measure(void){
    CLRWDT();               // feed the dog
    
    if(polledMeasurement == true) // only blink LED if it's a polled measurement
    {
        SoundLevel_LedOn();     // show 'active'
    }
    
    // initialize control variables
    sampling = true;
    sampleCounter = 0;
    presSumSquared = 0;
    
    // power-on microphone and amplifier circuit
    if(thresholdEnabled == false) // if polled measurement, than duty cycle power to MIC
    {
        powerMic_SetHigh();
        __delay_ms(100);         // wait until stable
    }else{
        powerMic_SetHigh();
    }
    SoundLevel_StartADC();  // ADC conversion will be handled by 
                            // SoundLevel_GetSample callback
    
    // wait until measurement is complete
    while(sampling) CLRWDT();
    
    // stop conversions and power-down analog circuitry
    SoundLevel_StopADC();
    if(thresholdEnabled == false) // if polled measurement, than duty cycle power to MIC
    {
        powerMic_SetLow();
    }
    
    // prepare measurement for transmission
    SoundLevel_PrepareData();
}

#endif
#endif
