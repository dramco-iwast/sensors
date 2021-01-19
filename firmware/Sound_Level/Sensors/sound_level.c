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
//#define V_SUPPLY        3.3 // measured voltage when sampling
#define V_SUPPLY        2.048
#define ADC_SCALE       4095
#define REF_PRESSURE    20e-6
#define DBZ_MAX         106
#define SCALE_FACTOR    600

#define ENABLE  1
#define DISABLE 0
#define WOS     2

#define DB_65            65*SCALE_FACTOR
#define DB_77            77*SCALE_FACTOR
#define DB_89            89*SCALE_FACTOR


//#define DEBUG_THRESHOLD

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

// Interrupt service routine for wake from MIC
void ISR_MIC_Wake(void);

// setup input interrupt pin from MIC
void DOUT_Init(void);


void VDDAMP_Init();
void VDDBIAS_Init();

void AMPS_enable(bool enable);

void MIC_Mode(uint8_t mode);

void ADC_Fixed_Voltage_Ref(uint8_t mode);


void THRESHOLD_Init();

/* local variables ************************************************************/

bool soundinterrupt = false; // variable to keep track of interrupt on MIC

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

uint16_t sampleArray[SAMPLES];

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
    // startup animation
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
    powerMic_SetLow(); // prevents it from powering the MIC the in the time before the first measurement when sensor is in polled mode
}

void nWakeMic_Init(void)
{
    nWakeMic_SetDigitalMode();
    nWakeMic_SetDigitalOutput();
    nWakeMic_SetLow();
}

void MIC_Mode(uint8_t mode)
{
    switch(mode)
    {
        case ENABLE:
            nWakeMic_SetLow();
            break;

        case WOS:
            nWakeMic_SetHigh();
            break;
            
        default:
            nWakeMic_SetLow();
    }
}

void READY_Init(void)
{
    READY_SetDigitalOutput();
    READY_SetHigh();
}

void DOUT_Init(void)
{
    DOUT_SetDigitalMode();
    DOUT_SetDigitalInput();
}

void VDDAMP_Init()
{
    VDDAMP_SetDigitalMode();
    VDDAMP_SetDigitalOutput();
    VDDAMP_SetLow();
}

void VDDBIAS_Init()
{
    VDDBIAS_SetDigitalMode();
    VDDBIAS_SetDigitalOutput();
    VDDBIAS_SetLow();
    
    VDDBIASAMP_SetDigitalMode();
    VDDBIASAMP_SetDigitalOutput();
    VDDBIASAMP_SetLow();
}

void AMPS_enable(bool enable)
{
    switch(enable)
    {
        case ENABLE:
            VDDBIASAMP_SetHigh();
            VDDBIAS_SetHigh();
            VDDAMP_SetHigh();
            //__delay_ms(100);
            break;

        case DISABLE:
            VDDBIASAMP_SetLow();
            VDDBIAS_SetLow();
            VDDAMP_SetLow();
            break;
            
        default:
            VDDBIASAMP_SetLow();
            VDDBIAS_SetLow();
            VDDAMP_SetLow();
    }
}

void THRESHOLD_Init()
{
    THRESHOLD1_SetDigitalMode();
    THRESHOLD1_SetDigitalOutput();
    THRESHOLD1_SetLow();
    
    THRESHOLD2_SetDigitalMode();
    THRESHOLD2_SetDigitalOutput();
    THRESHOLD2_SetLow();
}


void WDT_Init(void)
{
    // initialize timer for periodic measurements   
//    WDTCON0 = 0x1C; // 16 second period
    WDTCON0 = 0x20; // 64 second period
    WDTCON1 = 0x07; // LFINTOSC, window 100%
}

/* Initialize peripherals needed for Sound Level detection */
void SoundLevel_Init(void){

    LED_Init(); // Initialize LED
    
    PMD0bits.IOCMD = 0; // Enable gpio clock
    
    THRESHOLD_Init();
    __delay_ms(1);
    
    powerMic_Init();    
    __delay_ms(1);
    nWakeMic_Init();
    __delay_ms(1);
    
    READY_Init();
    DOUT_Init();
    VDDAMP_Init();
    VDDBIAS_Init();
    __delay_ms(1);
    
#ifdef DEBUG_THRESHOLD
            powerMic_SetHigh();
            // default go to WOS mode
            __delay_ms(1);
            MIC_Mode(WOS);
            //__delay_ms(1000);
#endif
     
    // enable interrupt on change
    PIE0bits.IOCIE = 1;   
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF6 = 0;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN6 = 0;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP6 = 1;
    
    IOCCF6_SetInterruptHandler(ISR_MIC_Wake); // interrupt hander for 

    adcScaler = V_SUPPLY / (ADC_SCALE * SENSITIVITY * AMP_FACTOR);
    
    // initialize ADC
    ADCC_Initialize();
    ADCC_SetADIInterruptHandler(SoundLevel_GetSample);
    
    // setup watchdog (WWDT))
    WDT_Init();

#ifdef DEBUG_THRESHOLD    
    thresholdEnabled = true;
    thresholdLevel = 400*60;
#endif
}


void ADC_Fixed_Voltage_Ref(uint8_t mode){
    switch(mode)
    {
        case ENABLE:
            // Enable FVR module
            PMD0bits.FVRMD = 0;
            while(!FVRCONbits.FVRRDY); // Wait until voltage is stable
            FVRCON = 0x82; // Enable Fixed voltage reference
            break;

        case DISABLE:
            FVRCON = 0x00; // Disable the Fixed voltage reference
            // Disable FVR module
            PMD0bits.FVRMD = 1;
            break;
            
        default:
            FVRCON = 0x00; // Disable the Fixed voltage reference
    }
}

/* Measure the sound level (MCU remains active)
 */
void SoundLevel_Measure(){
    polledMeasurement = true;
}

/* Main sensor loop
 */
void SoundLevel_Loop(void){
    
    if(polledMeasurement && (WDTCON0bits.SEN == 0)) // poll with WDT off
    {
        if(thresholdEnabled) // if threshold enabled
        {
            measurementRunning = true;
            measure(); // measure
            measurementRunning = false;
            
            generateInt();
            
            MIC_Mode(WOS);
            
            polledMeasurement = false; // clear polled measurement bool
        }
        else if(!thresholdEnabled) // if threshold disabled
        {
            powerMic_SetHigh(); // enable MIC
            __delay_ms(1);

            measurementRunning = true;
            measure(); // measure
            measurementRunning = false;
            
            generateInt();

            powerMic_SetLow(); // disable MIC
            __delay_ms(1);
            MIC_Mode(ENABLE); // disable WOS
            
            polledMeasurement = false; // clear polledmeasurement bool
        }
    }
    else if(polledMeasurement && (WDTCON0bits.SEN == 1)) // poll with WDT on
    {
        powerMic_SetHigh(); // enable MIC
        __delay_ms(1);
        
        measurementRunning = true;
        measure(); // measure
        measurementRunning = false;
        
        generateInt();
        
        MIC_Mode(WOS); // enable WOS mode
        
        WDTCON0bits.SEN = 0; // disable WDT
        
        polledMeasurement = false; // clear polledmeasurement bool
    }
    else if(soundinterrupt) // event MIC
    {   
        measurementRunning = true;
        measure(); // measure
        measurementRunning = false;
        
        if(overThreshold)
        {
            CLRWDT(); // reset WDT
            WDTCON0bits.SEN = 1; // enable WDT
            
            generateInt(); // interrupt to motherboard
            
            powerMic_SetLow(); // disable MIC
            MIC_Mode(ENABLE); // disable WOS
        }else
        {
            MIC_Mode(ENABLE);
            __delay_ms(10);
            
            MIC_Mode(WOS); // enable WOS
        }
        
        soundinterrupt = false; // clear soundinterrupt bool
    }
    else if(STATUSbits.nTO == 0) // WDT time-out
    {
        WDTCON0bits.SEN = 0; // disable WDT
        
        powerMic_SetHigh(); // enable MIC
        __delay_ms(1);
        MIC_Mode(WOS); // enable WOS
        
        EnterSleep();
    }
    else
    {
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
        
        if(thresholdEnabled)
        {
            powerMic_SetHigh(); // enable MIC
            __delay_ms(1);
            MIC_Mode(WOS); // MIC in WOS mode
            
            // TODO code to enable resistor circuit
            // TH1  TH2     TOT R   WoS Threshold
            // LOW  LOW     331k    89dBSPL
            // HIGH LOW     69k     77dBSPL
            // LOW  HIGH    17k     65dBSPL
            
            if(thresholdLevel < DB_77)
            {
                // set WoS to 65dB
                THRESHOLD1_SetHigh();
                THRESHOLD2_SetHigh();
            }
            else if(thresholdLevel < DB_89)
            {
                // set WoS to 77dB
                THRESHOLD1_SetLow();
                THRESHOLD2_SetHigh();
            }
            else
            {
                // set WoS to 89dB
                THRESHOLD1_SetLow();
                THRESHOLD2_SetLow();
            }
            
        }
    }
}

/* Prepare data for transmission */
void SoundLevel_PrepareData(){
    float dBZ = 0;
    
    // calculate mean value of samples to obtain the DC offset
    float mean = 0;
    for(int i=0; i<SAMPLES; i++)
    {
        mean += sampleArray[i];
    }
    mean /= SAMPLES;
    
    // calculate squared RMS value referenced to pressure
    for(int i=0; i<SAMPLES; i++)
    {
        float signal = (sampleArray[i] - mean) * adcScaler;
        signal *= signal;
        presSumSquared += signal;
    }
    
    //sqrt() also possible but easier to process with squared rms pressure values
    float presAvgSquared = presSumSquared/SAMPLES; 
    
    // avoid taking log10(0) which could result in a system hang
    if( (presAvgSquared/(REF_PRESSURE * REF_PRESSURE)) != 0.0 )
    {
        // 20 * log10( sqrt() ) -> 10 * log10( squared )
        dBZ = 10 * log10(presAvgSquared/(REF_PRESSURE * REF_PRESSURE));
    }else{
        dBZ = 0;
    }
    
    // constraint to max value
    if(dBZ > DBZ_MAX){
        dBZ = DBZ_MAX;
    }

    uint16_t dataToSend = (uint16_t)(round(dBZ * SCALE_FACTOR));

    measurementData[0] = (uint8_t)(dataToSend>>8);
    measurementData[1] = (uint8_t)(dataToSend);
    
    // notify motherboard
    if(dataToSend > thresholdLevel){
        overThreshold = true;
    }
    else{
        overThreshold = false;
    }
}

// This function is called when an ADC-conversion has completed
void SoundLevel_GetSample(){
    
    sampleArray[sampleCounter] = ADCC_GetConversionResult();
    
    sampleCounter++;
    if(sampleCounter>SAMPLES-1){ // we've taken enough samples
        SoundLevel_StopADC(); // stop conversions and power-down analog circuitry
        sampling = false; // reference to while(sampling), continue execution of program
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
    __delay_ms(1); // 1 ms interrupt                         
    READY_SetHigh();
}

void measure(void){
    
    ADC_Fixed_Voltage_Ref(ENABLE); // More accurate measurements

    SoundLevel_LedOn();

    MIC_Mode(ENABLE);
    __delay_ms(1); // short delay to stabilize microphone
    
    AMPS_enable(ENABLE); // enable amplifier circuits
    __delay_ms(20);
    SoundLevel_LedOff();    //  Short LED Blink to indicate measuring -- shortened to concerve battery power
    __delay_ms(180);
    
    // initialize control variables
    sampling = true;
    sampleCounter = 0;
    presSumSquared = 0;
    
    SoundLevel_StartADC();  // ADC conversion will be handled by 
                            // SoundLevel_GetSample callback
    while(sampling);
    
    AMPS_enable(DISABLE); // disable amplifier circuits
    
    ADC_Fixed_Voltage_Ref(DISABLE); // More accurate measurements
    
    SoundLevel_PrepareData(); // prepare measurement for transmission
    
//    SoundLevel_LedOff();
}


void ISR_MIC_Wake(void)
{
    // only generate interrupt if no measurements are running
    if(!measurementRunning)
    {
        soundinterrupt = true;
    }
}

#endif
#endif
