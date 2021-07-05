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
#include "string.h"
#include "../system/adcc.h"


#ifdef SENSOR_TYPE
#if (SENSOR_TYPE == POWER)
#warning "Compiling for Power sensor"
#include "veml7700.h"
#include "battery.h"
#include "util.h"

/*===================================*/
// Declaration global power struct
iwast_power_t power;
// Sensor settings
veml7700_settings veml7700_config;
/*===================================*/

/* Variables */
volatile uint8_t measurementData[2* M_NR];

void POWER_init_params()
{
    // Initialize struct to all zeros
    memset(&power, 0, sizeof(power));
}

void WDT_Init(void)
{
    // initialize timer for periodic measurements   
    WDTCON0 = 0x1C; // 16 second period
//    WDTCON0 = 0x20; // 64 second period    
    WDTCON1 = 0x07; // LFINTOSC, window 100%
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
    
    // Init needed variables
    POWER_init_params();

    // Set settings - with these setting, the sensor should consume about 2 uA
    veml7700_config.threshold_high = 0;
    veml7700_config.threshold_low = 0;
    veml7700_config.gain = VEML7700_GAIN_X1;
    veml7700_config.integration_time = VEML7700_INTEGRATION_TIME_100MS;
    veml7700_config.persistence = VEML7700_PERSISTENCE_1;
    veml7700_config.interrupts = VEML7700_INTERRUPT_ENABLE;
    veml7700_config.powersave_en = VEML7700_PS_ENABLE;
    veml7700_config.powersave = VEML7700_PS_MODE4;
    veml7700_config.shutdown = VEML7700_POWER_ON;
    
    // Light sensor
    veml7700_power(VEML7700_POWER_ENABLE);
    // Init Light Sensor
    veml7700_init(&veml7700_config, &power.meas.light.data);  
    
    // Ready pin to motherboard
    comm_init();
    
    // Init LEDS
    LED_Init();
    
    // Init battery measurements
    battery_init();
    power.meas.batt.voltage = battery_measure(); // Initial measurement
    
    // Init Watchdog
    WDT_Init();  
}

void Power_Measure(){
    power.ctrl.startMeasurement = true;
}

void check_thresholds_exceeded(void)
{
    if(power.batt_threshold.enabled) //  Only set Thresholds when in threshold mode
    {
        /* Threshold operation */
        if(power.meas.batt.voltage < power.batt_threshold.thresholdLevelLow){
            power.batt_threshold.underThreshold = true;
        }else if(power.meas.batt.voltage > power.batt_threshold.thresholdLevelHigh){
            power.batt_threshold.overThreshold = true;
        }
    }

    if(power.light_threshold.enabled) //  Only set Thresholds when in threshold mode
    {
        // Check sensor interrupt register for exceeded thresholds
//        veml7700_getIntStatus(power.light_threshold.underThreshold, power.light_threshold.overThreshold);
        
        if(power.meas.light.data.lux < power.light_threshold.thresholdLevelLow){
            power.light_threshold.underThreshold = true;
        }else if(power.meas.light.data.lux > power.light_threshold.thresholdLevelHigh){
            power.light_threshold.overThreshold = true;
        }
    }
}

void Measure()
{
    // Measure battery voltage
    power.meas.batt.voltage = battery_measure();
    
    // Get data from light sensor
    LED0_SetHigh(); // Led on
    veml7700_getALS(&power.meas.light.data, &veml7700_config);
    __delay_ms(20);
    LED0_SetLow();  // Led off
    
    // Check if any thresholds are exceeded - notify loop
    check_thresholds_exceeded();
    
    if(power.meas.light.data.lux > 65535){    //  Limit of the 2 byte format
        power.meas.light.data.lux = 65535;
    }
    
    uint16_t datalux = (uint16_t)(round(power.meas.light.data.lux));  //  Do not multiply lux value by 600
    
    // prepare data for I2C transmission: multiply by 600
    uint16_t databatvoltage = (uint16_t)(round(power.meas.batt.voltage * 10000)); //  multiply by 10000 as in iWAST configurator
    
    measurementData[0] = (uint8_t)(databatvoltage>>8);
    measurementData[1] = (uint8_t)(databatvoltage);

    measurementData[2] = (uint8_t)(datalux>>8);
    measurementData[3] = (uint8_t)(datalux);
}


void Power_Loop(){

    if(!power.ctrl.measurementRunning)
    {
        if(power.ctrl.startMeasurement)            //  Polled measurement
        {
            power.ctrl.startMeasurement = false;
            
            if(WDTCON0bits.SEN == 1)
            {
                WDTCON0bits.SEN = 0;    //  Disable WDT
                
                power.ctrl.measurementRunning = true;
                Measure();              //  Measure
                power.ctrl.measurementRunning = false;
                
                generateInt();     //  generate interrupt
                CLRWDT();               //  Reset wdt timer
                WDTCON0bits.SEN = 1;    //  enable WDT
            }else if(WDTCON0bits.SEN == 0)
            {
                power.ctrl.measurementRunning = true;
                Measure();              //  Measure
                power.ctrl.measurementRunning = false;
                
                generateInt();     //  generate interrupt 
            }
        }else if(STATUSbits.nTO == 0)   //  WDT Timeout
        {
            WDTCON0bits.SEN = 0;        //  Disable WDT
            
            // Set timeout to 16 sec
            WDTCON0 = 0x1C; // 16 second period
            
            power.ctrl.measurementRunning = true;
            Measure();              //  Measure
            power.ctrl.measurementRunning = false;
            
            // If threshold is exceeded - send interrupt
            if(power.batt_threshold.underThreshold || power.light_threshold.underThreshold 
                    || power.batt_threshold.overThreshold || power.light_threshold.overThreshold)
            {
                power.batt_threshold.underThreshold = false; //  Reset the states
                power.light_threshold.underThreshold = false;
                power.batt_threshold.overThreshold = false;
                power.light_threshold.overThreshold= false;
                
                generateInt();   
                
                // If threshold is exceeded - set watchdog period to 64 sec
                WDTCON0 = 0x20; // 64 second period  
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
    *length = 4; // this is fixed (M_NR = 2)
    data[0] = measurementData[0];
    data[1] = measurementData[1];
    data[2] = measurementData[2];
    data[3] = measurementData[3];
}

void Power_SetThreshold(uint8_t metric, uint8_t * thresholdData){
    
    uint16_t temp;
    
    if(metric == METRIC_BATT)     //  Batt Thresholds
    {
        power.batt_threshold.enabled = thresholdData[0];
        temp = (uint16_t)((thresholdData[1]<<8) | thresholdData[2]);
        power.batt_threshold.thresholdLevelLow = (float) temp / 10000;
        temp = (uint16_t)((thresholdData[3]<<8) | thresholdData[4]);
        power.batt_threshold.thresholdLevelHigh = (float) temp / 10000;   //  Divide thresholds by 100 as in iWAST configurator
    }
    if(metric == METRIC_LIGHT)     //  LDR Thresholds
    {
        power.light_threshold.enabled = thresholdData[0];
        temp = (uint16_t)((thresholdData[1]<<8 | thresholdData[2]));
        power.light_threshold.thresholdLevelLow = (float) temp;
        temp = (uint16_t)((thresholdData[3]<<8 | thresholdData[4]));
        power.light_threshold.thresholdLevelHigh = (float) temp;
    }
    
    if(power.batt_threshold.enabled || power.light_threshold.enabled)         //  Threshold -> enable WDT   
    {
        WDTCON0bits.SEN = 0;
        CLRWDT();
        WDTCON0bits.SEN = 1;
    }else{                          //  No thresholds -> WDT off 
        WDTCON0bits.SEN = 0;
    }
    
    // If enabled - set thresholds to veml7700 registers
    if(power.light_threshold.enabled)
    {
        // Set thresholds
        veml7700_setALS_WH((uint16_t) power.light_threshold.thresholdLevelHigh);
        veml7700_setALS_WL((uint16_t) power.light_threshold.thresholdLevelLow);
    }
}

#endif
#endif