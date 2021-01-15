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
 *         File: power.c
 *      Created: 2020-11-27
 *       Author: Jona Cappelle
 *      Version: 0.2
 *
 *  Description: Power Module Implementation
 *
 */

#include "power.h"
#include <math.h>
#include "../system/adcc.h"

#ifdef SENSOR_TYPE
#if (SENSOR_TYPE == POWER)
#warning "Compiling for Power sensor"


#define POWERV2


#define LDR_VOLT   0x13
#define BAT_VOLT   0x14

#define METRIC_BATT     0
#define METRIC_LIGHT    1

/* Forward declaration */
void measureVolt(void);
void initializePowerModule(void);
uint16_t GetSingleConversion(uint8_t channel);
void generateIntPower(void);
void LED_Blink(void);
void ADC_Init(void);
void ADC_Fixed_Voltage_Ref(uint8_t mode);
void Enter_sleep(void);

/*======= Modification Pierre =======*/

// Initialize watchdog timer
void WDT_Init(void);

// Variables

bool batThresholdEnabled = false;
uint16_t batThresholdLevelHigh = 0;
uint16_t batThresholdLevelLow = 0;

bool ldrThresholdEnabled = false;
uint16_t ldrThresholdLevelHigh = 0;
uint16_t ldrThresholdLevelLow = 0;

bool overThresholdBatt = false;
float floatBatThresholdLevelHigh = 0.0;

bool underThresholdBatt = false;
float floatBatThresholdLevelLow = 0.0;

bool overThresholdLDR = false;
float floatLDRThresholdLevelHigh = 0.0;

bool underThresholdLDR = false;
float floatLDRThresholdLevelLow = 0.0;

/*===================================*/

/* Variables */
bool startMeasurement = false;
bool measurementRunning = false;
volatile uint8_t measurementData[2* M_NR];
float floatldrvoltage;
float floatbatvoltage;
uint16_t ldrvoltage = 0;
uint16_t tempValue = 0;
uint16_t batvoltage = 0;
uint8_t batteryundervoltage = 0;

float LDR = 0.0;
float lux = 0.0;


#define ENABLE  1
#define DISABLE 0


/* Animation when Sound Module is plugged in */
void LED_Blink(void)
{
    // startup animation
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(100);
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(100);
    LED0_SetHigh();
    __delay_ms(100);
    LED0_SetLow();
    __delay_ms(500);
    
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
    __delay_ms(100);
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
    __delay_ms(100);
    LED1_SetHigh();
    __delay_ms(100);
    LED1_SetLow();
}

void WDT_Init(void)
{
    // initialize timer for periodic measurements   
//    WDTCON0 = 0x1C; // 16 second period
    WDTCON0 = 0x20; // 64 second period    
    WDTCON1 = 0x07; // LFINTOSC, window 100%
}

void ADC_Init(){
    
    // Enable ADC peripheral
    PMD3bits.ADCMD = 0; 
    
    // Enable FVR module
    PMD0bits.FVRMD = 0;
    
    // Enable Fixed voltage reference with voltage of 2.048 V
    FVRCON = 0x82;
    // set the ADCC to the options selected in the User Interface
    // ADLTH 0; 
    ADLTHL = 0x00;
    // ADLTH 0; 
    ADLTHH = 0x00;
    // ADUTH 0; 
    ADUTHL = 0x00;
    // ADUTH 0; 
    ADUTHH = 0x00;
    // ADSTPT 0; 
    ADSTPTL = 0x00;
    // ADSTPT 0; 
    ADSTPTH = 0x00;
    // ADACC 0; 
    ADACCU = 0x00;
    // ADRPT 0; 
    ADRPT = 0x00;
    // ADPCH ANA0; 
    ADPCH = 0x00;
    // ADACQ 0; 
    ADACQL = 0x00;
    // ADACQ 0; 
    ADACQH = 0x00;
    // ADCAP Additional uC disabled; 
    ADCAP = 0x00;
    // ADPRE 0; 
    ADPREL = 0x00;
    // ADPRE 0; 
    ADPREH = 0x00;
    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL Vss; 
    ADCON1 = 0x00;
    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS RES; 
    ADCON2 = 0x00;
    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x00;
    // ADMATH registers not updated; 
    ADSTAT = 0x00;
    // ADNREF VSS; ADPREF FVR; 
    ADREF = 0x03;
    // ADACT disabled; 
    ADACT = 0x00;
    // ADCS FOSC/2; 
    ADCLK = 0x00;
    //  ADCLK = 0x07;
    //  Doesnt matter, since we're just doing a single conversion
    //  I've changed it back to the default value
    //  TODO
    
    // ADGO stop; ADFM right; ADON enabled; ADCS FOSC/ADCLK; ADCONT disabled; 
    ADCON0 = 0x84;
    
    FVRCON = 0x00; // Disable fixed voltage reference
}

void ADC_Fixed_Voltage_Ref(uint8_t mode){
    switch(mode)
    {
        case ENABLE:
            FVRCON = 0x82; // Enable Fixed voltage reference
            break;

        case DISABLE:
            FVRCON = 0x00; // Disable the Fixed voltage reference
            break;
            
        default:
            FVRCON = 0x00; // Disable the Fixed voltage reference
    }
}

void Enter_sleep(){
    /* Go to sleep */
    CPUDOZEbits.IDLEN = 0; // make sure PIC is not in doze mode before going to sleep   
    NOP();
    SLEEP(); // enter sleep
    NOP();
    NOP();
}


void Power_Init(){
    
    PMD0bits.IOCMD = 0; // Enable gpio clock
    
    READY_SetDigitalMode();
    READY_SetDigitalOutput();
    READY_SetHigh();
    
    ADC_Init();
    
    LDR_MEAS_EN_SetDigitalMode();
    BAT_MEAS_EN_SetDigitalMode();
    
    LDR_MEAS_EN_SetDigitalOutput();
    BAT_MEAS_EN_SetDigitalOutput();

    LED0_SetDigitalMode();
    LED1_SetDigitalMode();
    
    LED0_SetDigitalOutput();
    LED1_SetDigitalOutput();
    
    LED0_SetLow();
    LED1_SetLow();

    LDR_MEAS_EN_SetLow();
    BAT_MEAS_EN_SetLow();
    
    LDR_VOLT_SetDigitalInput();
    LDR_VOLT_SetAnalogMode();
    
    BAT_VOLT_SetDigitalInput(); 
    BAT_VOLT_SetAnalogMode();
    
#ifdef POWERV2
    NCHG_SetDigitalMode();
    NCHG_SetDigitalInput();
#endif
    
    WDT_Init();
    
    /* Test blink LED */
    LED_Blink();    
}

void Power_Measure(){
    startMeasurement = true;
}

void Measure(){

    ADC_Fixed_Voltage_Ref(ENABLE);
    
    LDR_MEAS_EN_SetHigh();                              // Enable loadswitch to measure voltage
    BAT_MEAS_EN_SetHigh();                              // Enable loadswitch to measure voltage

    LED1_SetHigh();
    LED0_SetHigh();

    __delay_ms(20);                                     // Delay for settling voltages, 10ms is not long enough

    ADREFbits.PREF0 = 0;   //  Reference voltage to VDD (3V3)
    ADREFbits.PREF1 = 0;
    
    ADCC_GetSingleConversion(LDR_VOLT);                 // first measurement afte reset seems to be fixed and need to be rejected
    ldrvoltage = ADCC_GetSingleConversion(LDR_VOLT);

    tempValue = ADCC_GetSingleConversion(LDR_VOLT);
    if(tempValue < ldrvoltage){                         // To make sure it is the lowest/ stable voltage that is captured
        ldrvoltage = tempValue;
    }
    ADREFbits.PREF0 = 1;   //  Reference voltage to FVR module (2.048 V)
    ADREFbits.PREF1 = 1;
            
    floatldrvoltage = ((float)ldrvoltage /4096) * 3.3;    //  Convert ADC calue to voltage

    //  equation calculated from actual measurements with LUX meter - see also excel table in iWAST folder
    LDR = ( ( 4700 * 3.3 ) / floatldrvoltage ) - 4700;    //  Calculate LDR resistance value (ohm) with R = 4.7k and gamma = 0.7
    lux = 50000000 * pow( (double) LDR, -1.423 );
    
    if(lux > 65535){    //  Limit of the 2 byte format
        lux = 65535;
    }
    
    ADCC_GetSingleConversion(BAT_VOLT); 
    batvoltage = ADCC_GetSingleConversion(BAT_VOLT);
    floatbatvoltage = ((float)batvoltage /4096) * 2.048 * ((10+8.2)/8.2);   // Convert ADC value to voltage (Resistor divider)

    LDR_MEAS_EN_SetLow();                               // Disable loadswitch to measure voltage
    BAT_MEAS_EN_SetLow();                               // Disable loadswitch to measure voltage

    LED0_SetLow();
    LED1_SetLow();

    /* Check for battery empty */
    if(floatbatvoltage < 3.3){
        batteryundervoltage = 1;
    }

    /* If battery is charging again, unset the batteryundervoltage parameter */
    if(batteryundervoltage == 1){
        if(floatbatvoltage>3.5){
            batteryundervoltage = 0;
        }
    }
    
    if(batThresholdEnabled) //  Only set Thresholds when in threshold mode
    {
        /* Threshold operation */
        if(floatbatvoltage < floatBatThresholdLevelLow){
            underThresholdBatt = true;
        }

        if(floatbatvoltage > floatBatThresholdLevelHigh){
            overThresholdBatt = true;
        }
    }
    
    if(ldrThresholdEnabled) //  Only set Thresholds when in threshold mode
    {
        if(lux < floatLDRThresholdLevelLow){
            underThresholdLDR = true;
        }
        if(lux > floatLDRThresholdLevelHigh){
            overThresholdLDR = true;
        }
    }
    
    // prepare data for I2C transmission: multiply by 600
    uint16_t databatvoltage = (uint16_t)(round(floatbatvoltage * 10000)); //  multiply by 10000 as in iWAST configurator
    uint16_t datalux = (uint16_t)(round(lux));  //  Do not multiply lux value by 600
    
    measurementData[0] = (uint8_t)(databatvoltage>>8);
    measurementData[1] = (uint8_t)(databatvoltage);

    measurementData[2] = (uint8_t)(datalux>>8);
    measurementData[3] = (uint8_t)(datalux);

    measurementData[4] = (uint8_t)(batteryundervoltage);
    measurementData[5] = 0x00;
    
    //  TODO: check if it's necessary to enable and disable fixed voltage ref every time
    ADC_Fixed_Voltage_Ref(DISABLE);
}

//  TODO needs changes
void Power_Loop(){

    if(!measurementRunning)
    {
        if(startMeasurement)            //  Polled measurement
        {
            startMeasurement = false;
            
            if(WDTCON0bits.SEN == 1)
            {
                WDTCON0bits.SEN = 0;    //  Disable WDT
                
                measurementRunning = true;
                Measure();              //  Measure
                measurementRunning = false;
                
                generateIntPower();     //  generate interrupt
                CLRWDT();               //  Reset wdt timer
                WDTCON0bits.SEN = 1;    //  enable WDT
            }else if(WDTCON0bits.SEN == 0)
            {
                measurementRunning = true;
                Measure();              //  Measure
                measurementRunning = false;
                
                generateIntPower();     //  generate interrupt 
            }
        }else if(STATUSbits.nTO == 0)   //  WDT Timeout
        {
            WDTCON0bits.SEN = 0;        //  Disable WDT
            
            measurementRunning = true;
            Measure();              //  Measure
            measurementRunning = false;
            
            if(underThresholdBatt || underThresholdLDR || overThresholdBatt || overThresholdLDR)
            {
                underThresholdBatt = false; //  Reset the states
                underThresholdLDR = false;
                overThresholdBatt = false;
                overThresholdLDR = false;
                
                generateIntPower(); //  if battery voltage too low -> interrupt
            }
            CLRWDT();               //  Reset wdt timer
            WDTCON0bits.SEN = 1;    //  enable WDT
        }else
        {
            Enter_sleep();
        }
    }    
}

void Power_GetData(uint8_t * data, uint8_t  * length){
    *length = 6; // this is fixed (M_NR = 2)
    data[0] = measurementData[0];
    data[1] = measurementData[1];
    data[2] = measurementData[2];
    data[3] = measurementData[3];
    data[4] = measurementData[4];
    data[5] = measurementData[5];
}

void Power_SetThreshold(uint8_t metric, uint8_t * thresholdData){
    
    if(metric == METRIC_BATT)     //  Batt Thresholds
    {
        batThresholdEnabled = thresholdData[0];
        batThresholdLevelLow = (uint16_t)((thresholdData[1]<<8) | thresholdData[2]);
        floatBatThresholdLevelLow = (float) batThresholdLevelLow / 10000;
        batThresholdLevelHigh = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        floatBatThresholdLevelHigh = (float) batThresholdLevelHigh / 10000;   //  Divide thresholds by 100 as in iWAST configurator
    }
    if(metric == METRIC_LIGHT)     //  LDR Thresholds
    {
        ldrThresholdEnabled = thresholdData[0];
        ldrThresholdLevelLow = (uint16_t)((thresholdData[1]<<8 | thresholdData[2]));
        floatLDRThresholdLevelLow = (float) ldrThresholdLevelLow;
        ldrThresholdLevelHigh = (uint16_t)((thresholdData[3]<<8 | thresholdData[4]));
        floatLDRThresholdLevelHigh = (float) ldrThresholdLevelHigh;
    }
    
    if(batThresholdEnabled || ldrThresholdEnabled)         //  Threshold -> enable WDT   
    {
        WDTCON0bits.SEN = 0;
        CLRWDT();
        WDTCON0bits.SEN = 1;
    }else{                          //  No thresholds -> WDT off 
        WDTCON0bits.SEN = 0;
    }
}

void generateIntPower(void){
    READY_SetLow();
    __delay_ms(1);                          
    READY_SetHigh();
}

#endif
#endif